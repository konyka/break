# Editor / AnimationEditorWidgets

- module root: `Source/Editor/AnimationEditorWidgets`
- headers: 15; symbols: 749
- symbol kinds: class=17, delegate=32, enum=2, enumerator=11, function=159, macro=13, member=183, namespace=2, prototype=316, struct=8, typedef=6
- PrivateDependencyModuleNames: CoreUObject, Engine, GraphEditor, UnrealEd
- PublicDependencyModuleNames: AnimationCore, ApplicationCore, Core, InputCore, PropertyEditor, Slate, SlateCore, ToolMenus, ToolWidgets, WidgetRegistration

### `Source/Editor/AnimationEditorWidgets/Public/Overrides/OverrideStatusDetailsDisplayManager.h` (Public)


#### class `FOverrideStatusDetailsDisplayManager`  
`class FOverrideStatusDetailsDisplayManager : public FDetailsDisplayManager`  
_L19-74_
- inherits: `FDetailsDisplayManager`
- desc: The display manager is used to determine how the details view should behave when using an object filter. In this case the display manager is used to set the property-updated-widget (the override status widget).
- L29 _public prototype_ `virtual bool ShouldShowCategoryMenu() override;` — Returns a @code bool @endcode indicating whether this @code DetailsViewObjectFilter @endcode instance has a category menu
- L34 _public prototype_ `virtual const FDetailsViewStyleKey& GetDetailsViewStyleKey() const override;` — Returns the @code const FDetailsViewStyleKey& @endcode that is the Key to the current FDetailsViewStyle style
- L37 _public prototype_ `virtual bool CanConstructPropertyUpdatedWidgetBuilder() const override;` — Returns true if this manager can construct the property updated widget
- L40 _public prototype_ `virtual TSharedPtr<FPropertyUpdatedWidgetBuilder> ConstructPropertyUpdatedWidgetBuilder(const FConstructPropertyUpdatedWidgetBuilderArgs& Args) override;` — Returns the builder used to construct the property updated widgets, in this case the SOverrideStatusWidget
- L43 _public prototype_ `TSharedPtr<FOverrideStatusWidgetMenuBuilder> GetMenuBuilder(const FOverrideStatusSubject& InSubject) const;` — Returns the preconfigured menu builder for this display manager and a given subject
- L45 _public function_ `FOverrideStatus_CanCreateWidget& OnCanCreateWidget()`
- L46 _public function_ `FOverrideStatus_GetStatus& OnGetStatus()`
- L47 _public function_ `FOverrideStatus_OnWidgetClicked& OnWidgetClicked()`
- L48 _public function_ `FOverrideStatus_OnGetMenuContent& OnGetMenuContent()`
- L49 _public function_ `FOverrideStatus_AddOverride& OnAddOverride()`
- L50 _public function_ `FOverrideStatus_ClearOverride& OnClearOverride()`
- L51 _public function_ `FOverrideStatus_ResetToDefault& OnResetToDefault()`
- L52 _public function_ `FOverrideStatus_ValueDiffersFromDefault& OnValueDiffersFromDefault()`
- L56 _private prototype_ `TSharedPtr<FOverrideStatusDetailsWidgetBuilder> ConstructOverrideWidgetBuilder(const FConstructPropertyUpdatedWidgetBuilderArgs& Args);`
- L57 _private prototype_ `void OnObjectPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);`
- L58 _private prototype_ `void SetIsDisplayingOverrideableObject(bool InIsDisplayingOverrideableObject);`
- L60 _private member_ `bool bIsDisplayingOverrideableObject = false;`
- L62 _private member_ `FExecuteAction InvalidateCachedState;`
- L64 _private member_ `FOverrideStatus_CanCreateWidget CanCreateWidgetDelegate;`
- L65 _private member_ `FOverrideStatus_GetStatus GetStatusDelegate;`
- L66 _private member_ `FOverrideStatus_OnWidgetClicked WidgetClickedDelegate;`
- L67 _private member_ `FOverrideStatus_OnGetMenuContent GetMenuContentDelegate;`
- L68 _private member_ `FOverrideStatus_AddOverride AddOverrideDelegate;`
- L69 _private member_ `FOverrideStatus_ClearOverride ClearOverrideDelegate;`
- L70 _private member_ `FOverrideStatus_ResetToDefault ResetToDefaultDelegate;`
- L71 _private member_ `FOverrideStatus_ValueDiffersFromDefault ValueDiffersFromDefaultDelegate;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANIMATIONEDITORWIDGETS_API`

### `Source/Editor/AnimationEditorWidgets/Public/Overrides/OverrideStatusDetailsObjectFilter.h` (Public)


#### class `FOverrideStatusDetailsViewObjectFilter`  
`class FOverrideStatusDetailsViewObjectFilter : public FDetailsViewObjectFilter`  
_L19-66_
- inherits: `FDetailsViewObjectFilter`
- desc: An object filter for the property editor / details view. The filter can decide if it can display a certain object - in this case the object filter is used to provide the override status widget instead of the reset value arrow to the details panel.
- L24 _public function_ `template<typename T = FOverrideStatusDetailsViewObjectFilter> static TSharedPtr<T> Create()` — the standard method to create an object filter.
- L32 _public prototype_ `FOverrideStatusDetailsViewObjectFilter();` — default constructor
- L35 _public prototype_ `virtual void InitializeDisplayManager();` — sets up the  display manager for this filter
- L40 _public prototype_ `virtual TArray<FDetailsViewObjectRoot> FilterObjects(const TArray<UObject*>& SourceObjects) override;` — Given a const TArray<UObject*>& SourceObjects, filters the objects and puts the objects which should be shown in the Details panel in the return TArray<FDetailsViewObjectRoot>. These may be some part of the original SourceObjects array, itself, or it may be some contained sub-objects within the SourceObjects.
- L43 _public prototype_ `TSharedPtr<FOverrideStatusWidgetMenuBuilder> GetMenuBuilder(const FOverrideStatusSubject& InSubject) const;` — Returns a preconfigured menu builder for this filter.
- L45 _public prototype_ `FOverrideStatus_CanCreateWidget& OnCanCreateWidget();`
- L46 _public prototype_ `FOverrideStatus_GetStatus& OnGetStatus();`
- L47 _public prototype_ `FOverrideStatus_OnWidgetClicked& OnWidgetClicked();`
- L48 _public prototype_ `FOverrideStatus_OnGetMenuContent& OnGetMenuContent();`
- L49 _public prototype_ `FOverrideStatus_AddOverride& OnAddOverride();`
- L50 _public prototype_ `FOverrideStatus_ClearOverride& OnClearOverride();`
- L51 _public prototype_ `FOverrideStatus_ResetToDefault& OnResetToDefault();`
- L52 _public prototype_ `FOverrideStatus_ValueDiffersFromDefault& OnValueDiffersFromDefault();`
- L53 _public function_ `FOverrideStatusObjectFilter_CanMergeObjects& OnCanMergeObjects()`
- L55 _public prototype_ `static bool MergeObjectByClass(const UObject* InObjectA, const UObject* InObjectB);`
- L63 _private member_ `TSharedPtr<FOverrideStatusDetailsDisplayManager> OverrideStatusDisplayManager;` — The @code FOverrideStatusDetailsDisplayManager @endcode which provides an API to manage some of the characteristics of the details display
- L65 _private member_ `FOverrideStatusObjectFilter_CanMergeObjects CanMergeObjectDelegate;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMATIONEDITORWIDGETS_API`
- L11 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOverrideStatusObjectFilter_CanMergeObjects, const UObject*, const UObject*);`
- L11 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOverrideStatusObjectFilter_CanMergeObjects, const UObject*, const UObject*);`

### `Source/Editor/AnimationEditorWidgets/Public/Overrides/OverrideStatusDetailsWidgetBuilder.h` (Public)


#### class `FOverrideStatusDetailsWidgetBuilder`  
`class FOverrideStatusDetailsWidgetBuilder : public FPropertyUpdatedWidgetBuilder`  
_L16-64_
- inherits: `FPropertyUpdatedWidgetBuilder`
- desc: A Display builder for the override status combo button
- L19 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FOnGetWidget);`
- L30 _public prototype_ `FOverrideStatusDetailsWidgetBuilder( const TSharedRef<FOverrideStatusDetailsDisplayManager>& InDetailsDisplayManager, const TArray<FOverrideStatusObject>& InObjects, const TSharedPtr<const FPropertyPath>& InPropertyPath, const FName& InCategory);` — The constructor, which takes a @code TSharedRef<FDetailsDisplayManager> @endcode to initialize the Details Display Manager @param InDetailsDisplayManager the FDetailsDisplayManager which manages the details display than a property row
- L39 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Implements the generation of the Category Menu button SWidget
- L46 _public prototype_ `FOverrideStatus_CanCreateWidget& OnCanCreateWidget();`
- L47 _public prototype_ `FOverrideStatus_GetStatus& OnGetStatus();`
- L48 _public prototype_ `FOverrideStatus_OnWidgetClicked& OnWidgetClicked();`
- L49 _public prototype_ `FOverrideStatus_OnGetMenuContent& OnGetMenuContent();`
- L50 _public prototype_ `FOverrideStatus_AddOverride& OnAddOverride();`
- L51 _public prototype_ `FOverrideStatus_ClearOverride& OnClearOverride();`
- L52 _public prototype_ `FOverrideStatus_ResetToDefault& OnResetToDefault();`
- L53 _public prototype_ `FOverrideStatus_ValueDiffersFromDefault& OnValueDiffersFromDefault();`
- L61 _private member_ `TSharedRef<FOverrideStatusDetailsDisplayManager> DisplayManager;` — The @code DetailsDisplayManager @endcode which provides an API to manage some of the characteristics of the details display
- L63 _private member_ `FOverrideStatusSubject Subject;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMATIONEDITORWIDGETS_API`
- L19 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FOnGetWidget);`

### `Source/Editor/AnimationEditorWidgets/Public/Overrides/OverrideStatusSubject.h` (Public)


#### struct `FOverrideStatusObjectHandle`  
`template<typename T> struct FOverrideStatusObjectHandle`  
_L26-75_
- desc: A template handle pointing to given object type
- L30 _public function_ `FOverrideStatusObjectHandle() : Object(nullptr) , Key(NAME_None)`
- L36 _public function_ `FOverrideStatusObjectHandle(const T* InObject, const FName& InKey = NAME_None) : Object(InObject) , Key(InKey)`
- L42 _public function_ `bool IsValid() const`
- L47 _public function_ `operator bool() const`
- L52 _public function_ `const T* GetObject() const`
- L57 _public function_ `const FName& GetKey() const`
- L62 _public function_ `bool operator==(const FOverrideStatusObjectHandle& InOther) const`
- L67 _public function_ `const T* operator->() const`
- L73 _private member_ `const T* Object;`
- L74 _private member_ `FName Key;`

#### struct `FOverrideStatusObject`  
`struct FOverrideStatusObject`  
_L80-103_
- desc: A single object used within an override widget - the object is identified by a weak object pointer and a potential sub object key.
- L84 _public prototype_ `FOverrideStatusObject();`
- L85 _public prototype_ `FOverrideStatusObject(const UObject* InObject, const FName& InKey = NAME_None);`
- L87 _public prototype_ `FName GetFName() const;`
- L88 _public prototype_ `bool IsValid() const;`
- L89 _public prototype_ `const UObject* GetObject() const;`
- L90 _public prototype_ `const FName& GetKey() const;`
- L92 _public prototype_ `bool operator==(const FOverrideStatusObject& InOther) const;`
- L95 _public function_ `template<typename T> FOverrideStatusObjectHandle<T> GetHandle() const`
- L101 _private member_ `TWeakObjectPtr<const UObject> WeakObjectPtr;`
- L102 _private member_ `FName Key;`

#### struct `FOverrideStatusSubject`  
`struct FOverrideStatusSubject`  
_L111-288_
- desc: The subject of an override status (widget). To support multi selection the subject is represented by an array of objects and a property path. This class also offers helper template functions to facilitate the interaction between the list of subject object and the user interface layer.
- L114 _public prototype_ `FOverrideStatusSubject(const TArray<FOverrideStatusObject>& InObjects, const TSharedPtr<const FPropertyPath>& InPropertyPath, const FName& InCategory);`
- L115 _public prototype_ `FOverrideStatusSubject(const FOverrideStatusObject& InObject, const TSharedPtr<const FPropertyPath>& InPropertyPath = nullptr, const FName& InCategory = NAME_None);`
- L116 _public prototype_ `FOverrideStatusSubject(const UObject* InObject, const TSharedPtr<const FPropertyPath>& InPropertyPath = nullptr, const FName& InCategory = NAME_None, const FName& InKey = NAME_None);`
- L119 _public prototype_ `bool IsValid() const;` — returns true if any of the objects within the subject is still valid
- L122 _public prototype_ `int32 Num() const;` — returns the number of objects
- L125 _public prototype_ `const FOverrideStatusObject& operator [](int32 InIndex) const;` — array access operator
- L129 _public function_ `template<typename T> FOverrideStatusObjectHandle<T> GetHandle(int32 InIndex) const` — array handle access
- L135 _public function_ `TArray<FOverrideStatusObject>::RangedForConstIteratorType begin() const` — range access
- L136 _public function_ `TArray<FOverrideStatusObject>::RangedForConstIteratorType end() const`
- L139 _public prototype_ `bool HasPropertyPath() const;` — returns true if this subject contains a property path
- L142 _public prototype_ `const TSharedPtr<const FPropertyPath>& GetPropertyPath() const;` — getter for the property path
- L145 _public prototype_ `const FString& GetPropertyPathString(const TCHAR* Separator = TEXT("->")) cons` — getter for the propery path string (uses a cache inside and is faster than GetPropertyPath()->ToString())
- L148 _public prototype_ `bool HasCategory() const;` — returns true if this subject is linked to a category
- L151 _public prototype_ `const FName& GetCategory() const;` — getter for category
- L154 _public prototype_ `bool Contains(const FOverrideStatusObject& InObject) const;` — returns true if a given object is part of the subject
- L158 _public function_ `template<typename ObjectType> bool Contains() const` — returns true if the subject contains an object of type ObjectType
- L172 _public function_ `template<typename ObjectType = UObject> bool Contains(TFunction<bool(const FOverrideStatusObjectHandle<ObjectType>&)> InMatchPredicate) const` — returns true if the subject contains an object matching the given predicate
- L188 _public prototype_ `int32 Find(const FOverrideStatusObject& InObject) const;` — returns the index of a given object or INDEX_NONE
- L193 _public function_ `template<typename ObjectType = UObject> int32 Find(TFunction<bool(const FOverrideStatusObjectHandle<ObjectType>&)> InMatchPredicate) const` — returns the index of a given object or INDEX_NONE, the match is determined based on the given predicate
- L210 _public function_ `template<typename ObjectType = UObject> void ForEach(TFunction<void(const FOverrideStatusObjectHandle<ObjectType>&)> InPerObjectPredicate) const` — executes a given predicate for each object in the subject
- L224 _public function_ `template<typename ValueType, typename ObjectType = UObject> TOptional<ValueType> GetFirstValue(TFunction<TOptional<ValueType>(const FOverrideStatusObjectHandle<ObjectType>&)> InGetValuePerObjectPredicate) const` — returns the first valid value for a given predicate (or an unset TOptional). each object in the subject is interrogated for using the predicate and can return a TOptional indicating success.
- L245 _public function_ `template<typename ValueType, typename ObjectType = UObject> TOptional<ValueType> GetCommonValue(TFunction<TOptional<ValueType>(const FOverrideStatusObjectHandle<ObjectType>&)> InGetValuePerObjectPredicate) const` — returns a common for a given predicate (or an unset TOptional). each object in the subject is interrogated for using the predicate and can return a TOptional indicating success. if the value matches for all objects the value will be returned as a set TOptional, otherwise an unset TOptional will be returned.
- L275 _public function_ `template<typename ObjectType = UObject> TOptional<EOverrideWidgetStatus::Type> GetStatus(TFunction<TOptional<EOverrideWidgetStatus::Type>(const FOverrideStatusObjectHandle<ObjectType>&)> InGetValuePerObjectPredicate) const` — returns the status provided by the subject's objects or an empty TOptional if it varies across objects
- L281 _private member_ `TArray<FOverrideStatusObject> Objects;`
- L282 _private member_ `TSharedPtr<const FPropertyPath> PropertyPath;`
- L283 _private member_ `FName SubObjectKey;`
- L284 _private member_ `FName Category;`
- L286 _private member_ `mutable TOptional<FString> LastSeparator;`
- L287 _private member_ `mutable TOptional<FString> LastPropertyPathString;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMATIONEDITORWIDGETS_API`
- L13 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOverrideStatus_CanCreateWidget, const FOverrideStatusSubject&);`
- L13 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOverrideStatus_CanCreateWidget, const FOverrideStatusSubject&);`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EOverrideWidgetStatus::Type, FOverrideStatus_GetStatus, const FOverrideStatusSubject&);`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EOverrideWidgetStatus::Type, FOverrideStatus_GetStatus, const FOverrideStatusSubject&);`
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOverrideStatus_OnWidgetClicked, const FOverrideStatusSubject&, EOverrideWidgetStatus::Type);`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOverrideStatus_OnWidgetClicked, const FOverrideStatusSubject&, EOverrideWidgetStatus::Type);`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FOverrideStatus_OnGetMenuContent, const FOverrideStatusSubject&, EOverrideWidgetStatus::Type);`
- L16 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FOverrideStatus_OnGetMenuContent, const FOverrideStatusSubject&, EOverrideWidgetStatus::Type);`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOverrideStatus_AddOverride, const FOverrideStatusSubject&);`
- L17 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOverrideStatus_AddOverride, const FOverrideStatusSubject&);`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOverrideStatus_ClearOverride, const FOverrideStatusSubject&);`
- L18 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOverrideStatus_ClearOverride, const FOverrideStatusSubject&);`
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOverrideStatus_ResetToDefault, const FOverrideStatusSubject&);`
- L19 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOverrideStatus_ResetToDefault, const FOverrideStatusSubject&);`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOverrideStatus_ValueDiffersFromDefault, const FOverrideStatusSubject&);`
- L20 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOverrideStatus_ValueDiffersFromDefault, const FOverrideStatusSubject&);`

### `Source/Editor/AnimationEditorWidgets/Public/Overrides/OverrideStatusWidgetMenuBuilder.h` (Public)


#### class `FOverrideStatusWidgetMenuBuilder`  
`class FOverrideStatusWidgetMenuBuilder : public FToolElementRegistrationArgs`  
_L20-92_
- inherits: `FToolElementRegistrationArgs`
- desc: Builder for the override status menu that goes on the top right side of each property Component in the details panel
- L23 _private prototype_ `DECLARE_DELEGATE(FResetToDefault);`
- L30 _public prototype_ `FOverrideStatusWidgetMenuBuilder(const FOverrideStatusSubject& InSubject, const TWeakPtr<FOverrideStatusDetailsDisplayManager>& InDisplayManager = TWeakPtr<FOverrideStatusDetailsDisplayManager>());` — constructor
- L35 _public prototype_ `EOverrideWidgetStatus::Type GetStatus() const;` — returns the status of the override
- L38 _public function_ `TAttribute<EOverrideWidgetStatus::Type>& GetStatusAttribute()` — returns the attribute backing up the status of the override
- L43 _public prototype_ `void AddOverride();` — Override the active overrideable object at the given property path
- L44 _public prototype_ `bool CanAddOverride() const;`
- L45 _public prototype_ `FOverrideStatus_AddOverride& OnAddOverride();`
- L50 _public prototype_ `void ClearOverride();` — Clears any active overrides on the property / object
- L51 _public prototype_ `bool CanClearOverride() const;`
- L52 _public prototype_ `FOverrideStatus_ClearOverride& OnClearOverride();`
- L57 _public prototype_ `void ResetToDefault();` — Override the active overrideable object at the given property path
- L58 _public prototype_ `bool CanResetToDefault() const;`
- L59 _public prototype_ `FOverrideStatus_ResetToDefault& OnResetToDefault();`
- L60 _public prototype_ `FOverrideStatus_ValueDiffersFromDefault& OnValueDiffersFromDefault();`
- L65 _public prototype_ `void InitializeMenu();` — Set up the menu
- L70 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Fill this method in with your Slate to create it
- L76 _private member_ `TWeakObjectPtr<UToolMenu> ToolMenu;` — The UToolMenu providing the context menu
- L81 _private member_ `FOverrideStatusSubject Subject;` — The object that will be queried for its override state
- L86 _private member_ `TAttribute<EOverrideWidgetStatus::Type> StatusAttribute;` — The status wrapped as a property
- L88 _private member_ `FOverrideStatus_AddOverride AddOverrideDelegate;`
- L89 _private member_ `FOverrideStatus_ClearOverride ClearOverrideDelegate;`
- L90 _private member_ `FOverrideStatus_ResetToDefault ResetToDefaultDelegate;`
- L91 _private member_ `FOverrideStatus_ValueDiffersFromDefault ValueDiffersFromDefaultDelegate;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANIMATIONEDITORWIDGETS_API`
- L23 _delegate_ `DECLARE_DELEGATE(FResetToDefault);`

### `Source/Editor/AnimationEditorWidgets/Public/Overrides/SOverrideListWidget.h` (Public)


#### class `SOverrideListWidget`  
`class SOverrideListWidget : public SCompoundWidget`  
_L10-39_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS( SOverrideListWidget ) : _SubjectsHash(0)`
- L23 _public prototype_ `SOverrideListWidget();`
- L26 _public prototype_ `void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L32 _private member_ `TAttribute<uint32> SubjectsHashAttribute;`
- L33 _private member_ `TAttribute<TArray<FOverrideStatusSubject>> SubjectsAttribute;`
- L34 _private member_ `FOverrideStatus_GetStatus GetStatusDelegate;`
- L35 _private member_ `FOverrideStatus_ClearOverride ClearOverrideDelegate;`
- L37 _private member_ `TSharedPtr<STextBlock> TextBlock;`
- L38 _private member_ `TOptional<uint32> LastHash;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMATIONEDITORWIDGETS_API`

### `Source/Editor/AnimationEditorWidgets/Public/Overrides/SOverrideStatusWidget.h` (Public)


#### enum `EOverrideWidgetStatus::Type`  
`enum Type : int`  
_L15-25_
- L17 _public enumerator_ `None` — No override.
- L18 _public enumerator_ `Undetermined` — State has not yet been determine
- L19 _public enumerator_ `Uninitialized` — This property needs a value.\nYou won't be able to test or publish until you set one.
- L20 _public enumerator_ `Inherited` — This property's parent component has been overridden.
- L21 _public enumerator_ `ChangedHere` — This property has been overridden.
- L22 _public enumerator_ `ChangedInside` — At least one of this property's values has been overridden.
- L23 _public enumerator_ `ChangedOutside` — A parent property of this property has been overridden.
- L24 _public enumerator_ `Mixed` — The selected elements have mixed override states on this property.

#### struct `FOverrideStatusWidgetStyle`  
`struct FOverrideStatusWidgetStyle`  
_L28-36_
- L30 _public member_ `const FSlateBrush* Icon = nullptr;`
- L31 _public member_ `const FSlateBrush* HoveredIcon = nullptr;`
- L32 _public member_ `FText Tooltip;`
- L33 _public member_ `FSlateColor Color = FStyleColors::White;`
- L34 _public member_ `FSlateColor HoveredColor = FStyleColors::White;`
- L35 _public member_ `TOptional<FVector2D> IconSize;`

#### class `SOverrideStatusWidget`  
`class SOverrideStatusWidget : public SCompoundWidget`  
_L41-98_
- inherits: `SCompoundWidget`
- L45 _public function_ `SLATE_BEGIN_ARGS( SOverrideStatusWidget ) : _Status(EOverrideWidgetStatus::None) , _IsHovered(false)`
- L58 _public prototype_ `SOverrideStatusWidget();`
- L61 _public prototype_ `void Construct(const FArguments& InArgs);`
- L63 _public prototype_ `EOverrideWidgetStatus::Type GetStatus() const;`
- L64 _public prototype_ `void SetStatus(EOverrideWidgetStatus::Type InStatus);`
- L66 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L67 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L68 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L69 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L71 _public prototype_ `void QueueRepaint();`
- L73 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L75 _public prototype_ `static const FOverrideStatusWidgetStyle* GetStyleFromStatus(EOverrideWidgetStatus::Type InStatus);`
- L79 _private prototype_ `FReply HandleClick();`
- L80 _private prototype_ `static const FOverrideStatusWidgetStyle* GetStyleFromStatus_Fallback(EOverrideWidgetStatus::Type InStatus);`
- L86 _private member_ `const FOverrideStatusWidgetStyle* WidgetStyle;` — Style used for the button. Note that it is never null but does change
- L87 _private member_ `FOverrideStatusWidgetStyle DefaultWidgetStyle;`
- L88 _private member_ `TSharedPtr<SImage> Image;`
- L89 _private member_ `bool bAlwaysUpdateOnTick;`
- L90 _private member_ `bool bTickIsPending;`
- L91 _private member_ `TOptional<bool> bLastHovered;`
- L93 _private member_ `FOnGetContent OnGetMenuContent;`
- L94 _private member_ `FOnClicked OnClicked;`
- L95 _private member_ `TAttribute<EOverrideWidgetStatus::Type> StatusAttribute;`
- L96 _private member_ `FOverrideStatusWidgetGetStyle OnGetStyle;`
- L97 _private member_ `FOverrideStatusWidgetGetTooltip OnGetTooltip;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMATIONEDITORWIDGETS_API`
- L13 _namespace_ `namespace EOverrideWidgetStatus`
- L38 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(const FOverrideStatusWidgetStyle*, FOverrideStatusWidgetGetStyle, EOverrideWidgetStatus::Type);`
- L38 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(const FOverrideStatusWidgetStyle*, FOverrideStatusWidgetGetStyle, EOverrideWidgetStatus::Type);`
- L39 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FOverrideStatusWidgetGetTooltip, EOverrideWidgetStatus::Type);`
- L39 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FOverrideStatusWidgetGetTooltip, EOverrideWidgetStatus::Type);`

### `Source/Editor/AnimationEditorWidgets/Public/SchematicGraphPanel/SSchematicGraphPanel.h` (Public)


#### class `FSchematicGraphNodeDragDropOp`  
`class FSchematicGraphNodeDragDropOp : public FDragDropOperation`  
_L14-49_
- inherits: `FDragDropOperation`
- L17 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FSchematicGraphNodeDragDropOp, FDragDropOperation) static TSharedRef<FSchematicGraphNodeDragDropOp> New(TArray<SSchematicGraphNode*> InSchematicGraphNodes, const TArray<FGuid>& InElements);`
- L23 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L26 _public function_ `bool HasElements() const` — @return true if this drag operation contains property paths
- L32 _public function_ `const TArray<FGuid>& GetElements() const` — @return The property paths from this drag operation
- L38 _public prototype_ `const TArray<const FSchematicGraphNode*> GetNodes() const;` — @return The nodes being dragged
- L40 _public prototype_ `FString GetJoinedDecoratorLabels() const;`
- L45 _private member_ `TArray<SSchematicGraphNode*> SchematicGraphNodes;` — Nodes being dragged
- L48 _private member_ `TArray<FGuid> Elements;` — Data for the property paths this item represents

#### class `SSchematicGraphNode`  
`class SSchematicGraphNode : public SNodePanel::SNode`  
_L51-131_
- inherits: `SNodePanel::SNode`
- L55 _public typedef_ `typedef TAnimatedAttribute<FVector2d> FVector2dAttribute;`
- L56 _public typedef_ `typedef TAnimatedAttribute<float> FFloatAttribute;`
- L57 _public typedef_ `typedef TAnimatedAttribute<FLinearColor> FLinearColorAttribute;`
- L59 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnClicked, SSchematicGraphNode*, const FPointerEvent&);`
- L60 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnBeginDrag, SSchematicGraphNode*, const TSharedPtr<FDragDropOperation>&);`
- L61 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnEndDrag, SSchematicGraphNode*, const TSharedPtr<FDragDropOperation>&);`
- L62 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnDrop, SSchematicGraphNode*, const FDragDropEvent&);`
- L64 _public prototype_ `SLATE_BEGIN_ARGS(SSchematicGraphNode);`
- L65 _public prototype_ `SLATE_ARGUMENT(const FSchematicGraphNode*, NodeData) SLATE_ARGUMENT(TSharedPtr<FVector2dAttribute>, Position) SLATE_ARGUMENT(TSharedPtr<FVector2dAttribute>, Size) SLATE_ARGUMENT(TSharedPtr<FFloatAttribute>, Scale) SLATE_ATTRIBUTE(bool, EnableAutoScale) SLATE_ARGUMENT(TArray<TSharedPtr<FLinearColorAttribute>>, LayerColors) SLATE_ARGUMENT(TFunction<const FSlateBrush*(const FGuid&, int32)>, BrushGetter) SLATE_EVENT(FOnClicked, OnClicked) SLATE_EVENT(FOnBeginDrag, OnBeginDrag) SLATE_EVENT(FOnEndDrag, OnEndDrag) SLATE_EVENT(FOnDrop, OnDrop) SLATE_ATTRIBUTE(FText, ToolTipText) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L81 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L82 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L84 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L85 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L86 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L87 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L88 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L89 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L90 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L92 _public prototype_ `virtual EVisibility GetNodeVisibility() const;`
- L93 _public prototype_ `virtual FVector2f GetPosition2f() const override;`
- L94 _public prototype_ `void EnablePositionAnimation(bool bEnabled = true);`
- L96 _public function_ `const FVector2d& GetOriginalSize() const`
- L98 _public function_ `const FSchematicGraphNode* GetNodeData() const`
- L99 _public function_ `FSchematicGraphNode* GetNodeData()`
- L100 _public prototype_ `const FGuid GetGuid() const;`
- L101 _public prototype_ `bool IsInteractive() const;`
- L103 _public function_ `const bool IsBeingDragged() const`
- L104 _public prototype_ `const bool IsFadedOut() const;`
- L108 _private member_ `bool bIsBeingDragged = false;`
- L109 _private member_ `static inline const FVector2d DefaultNodeSize = FVector2d(32.0,32.0);`
- L110 _private member_ `FVector2d OriginalSize = DefaultNodeSize;`
- L112 _private member_ `TSharedPtr<FSchematicGraphNode> NodeData;`
- L113 _private member_ `TSharedPtr<FVector2dAttribute> Position;`
- L114 _private member_ `TOptional<FVector2d> PositionDuringDrag;`
- L115 _private member_ `TOptional<FVector2d> OffsetDuringDrag;`
- L116 _private member_ `TSharedPtr<FVector2dAttribute> Size;`
- L117 _private member_ `TSharedPtr<FFloatAttribute> Scale;`
- L118 _private member_ `TAttribute<bool> EnableAutoScale;`
- L119 _private member_ `TOptional<float> AutoScale;`
- L120 _private member_ `TArray<TSharedPtr<FLinearColorAttribute>> LayerColors;`
- L121 _private member_ `TFunction<const FSlateBrush*(const FGuid&, int32)> BrushGetter;`
- L122 _private member_ `FOnClicked OnClickedDelegate;`
- L123 _private member_ `FOnBeginDrag OnBeginDragDelegate;`
- L124 _private member_ `FOnEndDrag OnEndDragDelegate;`
- L125 _private member_ `FOnDrop OnDropDelegate;`
- L126 _private member_ `SSchematicGraphPanel* SchematicGraphPanel = nullptr;`
- L127 _private member_ `TSharedPtr<FFloatAttribute> ExpansionCircleFactor;`

#### class `SSchematicGraphPanel`  
`class SSchematicGraphPanel : public SNodePanel, public FTickableEditorObject`  
_L135-313_
- inherits: `SNodePanel,FTickableEditorObject`
- desc: Widget allowing editing of a control rig's structure
- L139 _public typedef_ `using FVector2dAttribute = SSchematicGraphNode::FVector2dAttribute;`
- L140 _public typedef_ `using FFloatAttribute = SSchematicGraphNode::FFloatAttribute;`
- L141 _public typedef_ `using FLinearColorAttribute = SSchematicGraphNode::FLinearColorAttribute;`
- L143 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnNodeClicked, SSchematicGraphPanel*, SSchematicGraphNode*, const FPointerEvent&);`
- L144 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnBeginDrag, SSchematicGraphPanel*, SSchematicGraphNode*, const TSharedPtr<FDragDropOperation>&);`
- L145 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnEndDrag, SSchematicGraphPanel*, SSchematicGraphNode*, const TSharedPtr<FDragDropOperation>&);`
- L146 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnEnterDrag, SSchematicGraphPanel*, const TSharedPtr<FDragDropOperation>&);`
- L147 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnLeaveDrag, SSchematicGraphPanel*, const TSharedPtr<FDragDropOperation>&);`
- L148 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnCancelDrag, SSchematicGraphPanel*, SSchematicGraphNode*, const TSharedPtr<FDragDropOperation>&);`
- L149 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnDrop, SSchematicGraphPanel*, SSchematicGraphNode*, const FDragDropEvent&);`
- L151 _public function_ `SLATE_BEGIN_ARGS(SSchematicGraphPanel)`
- L178 _public function_ `virtual ~SSchematicGraphPanel() override`
- L185 _public function_ `void SetSchematicGraph(FSchematicGraphModel* InGraphData)` — `UE_DEPRECATED(5.6, "SetSchematicGraph with raw pointer has been deprecated, please, use SetSchematicGraphModel with a weak pointer instead.")`
- L187 _public function_ `const FSchematicGraphModel* GetSchematicGraph() const` — `UE_DEPRECATED(5.6, "GetSchematicGraph with raw pointer has been deprecated, please, use GetSchematicGraphModel with a weak pointer instead.")`
- L189 _public function_ `FSchematicGraphModel* GetSchematicGraph()` — `UE_DEPRECATED(5.6, "GetSchematicGraph with raw pointer has been deprecated, please, use GetSchematicGraphModel with a weak pointer instead.")`
- L191 _public prototype_ `void SetSchematicGraphModel(TWeakPtr<FSchematicGraphModel> InGraphData);`
- L192 _public function_ `const TWeakPtr<const FSchematicGraphModel> GetSchematicGraphModel() const`
- L193 _public function_ `TWeakPtr<FSchematicGraphModel> GetSchematicGraphModel()`
- L194 _public prototype_ `void Construct(const FArguments& InArgs);`
- L196 _public prototype_ `void RebuildPanel();`
- L197 _public prototype_ `void AddNode(const FSchematicGraphNode* InNodeToAdd);`
- L198 _public prototype_ `void RemoveNode(const FSchematicGraphNode* InNodeToRemove);`
- L199 _public prototype_ `const SSchematicGraphNode* FindNode(const FGuid& InGuid) const;`
- L200 _public prototype_ `SSchematicGraphNode* FindNode(const FGuid& InGuid);`
- L201 _public prototype_ `void AddLink(const FSchematicGraphLink* InLinkToAdd);`
- L202 _public prototype_ `void RemoveLink(const FSchematicGraphLink* InLinkToRemove);`
- L203 _public prototype_ `const FSchematicLinkWidgetInfo* FindLink(const FGuid& InGuid) const;`
- L204 _public prototype_ `FSchematicLinkWidgetInfo* FindLink(const FGuid& InGuid);`
- L207 _public prototype_ `virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;` — SNodePanel interface
- L208 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L209 _public prototype_ `virtual void RemoveAllNodes() override;`
- L210 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L213 _public prototype_ `TSharedRef<SSchematicGraphNode> GetChild(int32 ChildIndex) const;`
- L216 _public prototype_ `virtual TStatId GetStatId() const override;` — FTickableEditorObject Interface
- L217 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L218 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L219 _public function_ `virtual bool IsTickable() const override`
- L222 _public prototype_ `void ToggleVisibility();`
- L223 _public prototype_ `void OnNodeClicked(SSchematicGraphNode* Node, const FPointerEvent& MouseEvent);`
- L224 _public prototype_ `void OnBeginDragEvent(SSchematicGraphNode* Node, const TSharedPtr<FDragDropOperation>& InDragDropEvent);`
- L225 _public prototype_ `void OnEndDragEvent(SSchematicGraphNode* Node, const TSharedPtr<FDragDropOperation>& InDragDropEvent);`
- L226 _public prototype_ `void OnEnterDragEvent(const TSharedPtr<FDragDropOperation>& InDragDropEvent);`
- L227 _public prototype_ `void OnLeaveDragEvent(const TSharedPtr<FDragDropOperation>& InDragDropEvent);`
- L228 _public prototype_ `void OnCancelDragEvent(SSchematicGraphNode* Node, const TSharedPtr<FDragDropOperation>& InDragDropEvent);`
- L229 _public prototype_ `void OnDropEvent(SSchematicGraphNode* Node, const FDragDropEvent& InDragDropEvent);`
- L230 _public prototype_ `FReply HandleNodeDragDetected(FGuid Guid, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L232 _public prototype_ `virtual FVector2d GetPositionForNode(FGuid InNodeGuid) const;`
- L233 _public prototype_ `virtual FLinearColor GetColorForNode(FGuid InNodeGuid, int32 InLayerIndex) const;`
- L234 _public prototype_ `virtual FText GetToolTipForNode(FGuid InNodeGuid) const;`
- L235 _public prototype_ `virtual float GetScaleForNode(FGuid InNodeGuid) const;`
- L236 _public prototype_ `void AdjustPositionWithDPIScale(FVector2d& InOutPosition, bool bInverse = false) const;`
- L238 _public prototype_ `virtual bool IsAutoGroupingEnabled() const;`
- L239 _public prototype_ `virtual float GetAutoGroupingDistance() const;`
- L241 _public prototype_ `virtual bool IsAutoScaleEnabledForNode(FGuid InNodeGuid) const;`
- L242 _public prototype_ `virtual float GetMinimumLinkDistanceForNode(FGuid InLinkGuid, bool bIncludeScale = true) const;`
- L244 _public function_ `FOnNodeClicked& OnNodeClicked()`
- L245 _public function_ `FOnBeginDrag& OnBeginDrag()`
- L246 _public function_ `FOnEndDrag& OnEndDrag()`
- L247 _public function_ `FOnEnterDrag& OnEnterDrag()`
- L248 _public function_ `FOnLeaveDrag& OnLeaveDrag()`
- L249 _public function_ `FOnCancelDrag& OnCancelDrag()`
- L250 _public function_ `FOnDrop& OnAcceptDrop()`
- L252 _public function_ `const FVector2d& GetNodeLabelOffset() const`
- L253 _public prototype_ `void IncrementNodeLabelOffset(const FVector2d& InOffset);`
- L257 _private prototype_ `void UpdatePerNodeCaches(bool bRemoveNodesFromAutoGroups);`
- L258 _private prototype_ `void UpdateAutoGroupingForNodes();`
- L259 _private prototype_ `void UpdateAutoScalingForNodes();`
- L261 _private member_ `bool bIsDragDropping = false;`
- L262 _private member_ `TSharedPtr<FDragDropOperation> DragDropOpFromOutside;`
- L263 _private member_ `bool bIsOverlay = false;`
- L264 _private member_ `int32 PaddingLeft = 0;`
- L265 _private member_ `int32 PaddingRight = 0;`
- L266 _private member_ `int32 PaddingTop = 0;`
- L267 _private member_ `int32 PaddingBottom = 0;`
- L268 _private member_ `int32 PaddingInterNode = 0;`
- L269 _private member_ `TWeakPtr<FSchematicGraphModel> GraphDataWeak;`
- L270 _private member_ `FOnNodeClicked OnNodeClickedDelegate;`
- L271 _private member_ `FOnBeginDrag OnBeginDragDelegate;`
- L272 _private member_ `FOnEndDrag OnEndDragDelegate;`
- L273 _private member_ `FOnEnterDrag OnEnterDragDelegate;`
- L274 _private member_ `FOnLeaveDrag OnLeaveDragDelegate;`
- L275 _private member_ `FOnCancelDrag OnCancelDragDelegate;`
- L276 _private member_ `FOnDrop OnDropDelegate;`
- L277 _private member_ `TMap<FGuid, TSharedPtr<SSchematicGraphNode>> NodeByGuid;`
- L300 _private member_ `TArray<FPerNodeCache> PerNodeCaches;`
- L301 _private member_ `TMap<FGuid, int32> GuidToNodeCache;`
- L302 _private member_ `TMap<uint32, FGuid> GroupNodeGuidByHash;`
- L304 _private member_ `TMap<FGuid, TSharedPtr<FSchematicLinkWidgetInfo>> LinkByGuid;`
- L306 _private member_ `mutable TMap<FGuid, FVector2d> NodeCenterByGuid;`
- L307 _private member_ `mutable TArray<FVector2d> NodeCenterByIndex;`
- L308 _private member_ `mutable TArray<ESchematicGraphVisibility::Type> NodeVisibilityByIndex;`
- L309 _private member_ `mutable TMap<FGuid, ESchematicGraphVisibility::Type> NodeVisibilityByGuid;`
- L310 _private member_ `mutable TOptional<FGuid> DropTarget;`
- L311 _private member_ `mutable TOptional<float> DPIScale;`
- L312 _private member_ `FVector2d NodeLabelOffset = FVector2d::ZeroVector;`

#### struct `SSchematicGraphPanel::FSchematicLinkWidgetInfo`  
`struct FSchematicLinkWidgetInfo`  
_L170-176_
- L172 _public member_ `TSharedPtr<FFloatAttribute> Minimum;`
- L173 _public member_ `TSharedPtr<FFloatAttribute> Maximum;`
- L174 _public member_ `TSharedPtr<FLinearColorAttribute> Color;`
- L175 _public member_ `TSharedPtr<FFloatAttribute> Thickness;`

#### struct `SSchematicGraphPanel::FPerNodeCache`  
`struct FPerNodeCache`  
_L279-298_
- L281 _public function_ `FPerNodeCache() : Guid() , Label() , bHasParent(false) , Visibility(ESchematicGraphVisibility::Visible) , bIsAutoScaling(false) , Position(FVector2d::ZeroVector) , Radius(0.0)`
- L291 _public member_ `FGuid Guid;`
- L292 _public member_ `FText Label;`
- L293 _public member_ `bool bHasParent;`
- L294 _public member_ `ESchematicGraphVisibility::Type Visibility;`
- L295 _public member_ `bool bIsAutoScaling;`
- L296 _public member_ `FVector2d Position;`
- L297 _public member_ `double Radius;`

#### Free symbols / members of external scopes

- L59 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnClicked, SSchematicGraphNode*, const FPointerEvent&);`
- L60 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBeginDrag, SSchematicGraphNode*, const TSharedPtr<FDragDropOperation>&);`
- L61 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnEndDrag, SSchematicGraphNode*, const TSharedPtr<FDragDropOperation>&);`
- L62 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDrop, SSchematicGraphNode*, const FDragDropEvent&);`
- L143 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnNodeClicked, SSchematicGraphPanel*, SSchematicGraphNode*, const FPointerEvent&);`
- L144 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnBeginDrag, SSchematicGraphPanel*, SSchematicGraphNode*, const TSharedPtr<FDragDropOperation>&);`
- L145 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnEndDrag, SSchematicGraphPanel*, SSchematicGraphNode*, const TSharedPtr<FDragDropOperation>&);`
- L146 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnEnterDrag, SSchematicGraphPanel*, const TSharedPtr<FDragDropOperation>&);`
- L147 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnLeaveDrag, SSchematicGraphPanel*, const TSharedPtr<FDragDropOperation>&);`
- L148 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnCancelDrag, SSchematicGraphPanel*, SSchematicGraphNode*, const TSharedPtr<FDragDropOperation>&);`
- L149 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnDrop, SSchematicGraphPanel*, SSchematicGraphNode*, const FDragDropEvent&);`

### `Source/Editor/AnimationEditorWidgets/Public/SchematicGraphPanel/SchematicGraphDefines.h` (Public)


#### enum `ESchematicGraphVisibility::Type`  
`enum Type : int`  
_L18-23_
- L20 _public enumerator_ `Visible`
- L21 _public enumerator_ `FadedOut`
- L22 _public enumerator_ `Hidden`

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSchematicGraph, Log, All);`
- L16 _namespace_ `namespace ESchematicGraphVisibility`
- L26 _delegate_ `DECLARE_EVENT_TwoParams(FSchematicGraph, FOnSchematicGraphTagAdded, const FSchematicGraphNode*, const FSchematicGraphTag*);`
- L26 _prototype_ `DECLARE_EVENT_TwoParams(FSchematicGraph, FOnSchematicGraphTagAdded, const FSchematicGraphNode*, const FSchematicGraphTag*);`
- L27 _delegate_ `DECLARE_EVENT_TwoParams(FSchematicGraph, FOnTagRemoved, const FSchematicGraphNode*, const FSchematicGraphTag*);`
- L27 _prototype_ `DECLARE_EVENT_TwoParams(FSchematicGraph, FOnTagRemoved, const FSchematicGraphNode*, const FSchematicGraphTag*);`
- L28 _delegate_ `DECLARE_EVENT_OneParam(FSchematicGraph, FOnSchematicGraphNodeAdded, const FSchematicGraphNode*);`
- L28 _prototype_ `DECLARE_EVENT_OneParam(FSchematicGraph, FOnSchematicGraphNodeAdded, const FSchematicGraphNode*);`
- L29 _delegate_ `DECLARE_EVENT_OneParam(FSchematicGraph, FOnNodeRemoved, const FSchematicGraphNode*);`
- L29 _prototype_ `DECLARE_EVENT_OneParam(FSchematicGraph, FOnNodeRemoved, const FSchematicGraphNode*);`
- L30 _delegate_ `DECLARE_EVENT_OneParam(FSchematicGraph, FOnSchematicGraphLinkAdded, const FSchematicGraphLink*);`
- L30 _prototype_ `DECLARE_EVENT_OneParam(FSchematicGraph, FOnSchematicGraphLinkAdded, const FSchematicGraphLink*);`
- L31 _delegate_ `DECLARE_EVENT_OneParam(FSchematicGraph, FOnLinkRemoved, const FSchematicGraphLink*);`
- L31 _prototype_ `DECLARE_EVENT_OneParam(FSchematicGraph, FOnLinkRemoved, const FSchematicGraphLink*);`
- L32 _delegate_ `DECLARE_EVENT(FSchematicGraph, FOnGraphReset);`
- L32 _prototype_ `DECLARE_EVENT(FSchematicGraph, FOnGraphReset);`
- L34 _macro_ `#define SCHEMATICGRAPHELEMENT_BODY_BASE(ClassName) \`
- L93 _macro_ `#define SCHEMATICGRAPHELEMENT_BODY(ClassName, SuperClass, BaseClass) \`

### `Source/Editor/AnimationEditorWidgets/Public/SchematicGraphPanel/SchematicGraphLink.h` (Public)


#### class `FSchematicGraphLink`  
`class FSchematicGraphLink : public TSharedFromThis<FSchematicGraphLink>`  
_L11-53_
- inherits: `TSharedFromThis<FSchematicGraphLink>`
- L15 _public function_ `SCHEMATICGRAPHELEMENT_BODY_BASE(FSchematicGraphLink) const FGuid& GetGuid() const`
- L18 _public function_ `static uint32 GetLinkHash(const FGuid& InSourceNodeGuid, const FGuid& InTargetNodeGuid)`
- L22 _public function_ `uint32 GetLinkHash() const`
- L23 _public function_ `const FGuid& GetSourceNodeGuid() const`
- L24 _public function_ `const FGuid& GetTargetNodeGuid() const`
- L25 _public function_ `virtual float GetMinimum() const`
- L26 _public function_ `virtual float GetMaximum() const`
- L27 _public function_ `virtual FVector2d GetSourceNodeOffset() const`
- L28 _public function_ `virtual FVector2d GetTargetNodeOffset() const`
- L29 _public function_ `virtual FLinearColor GetColor() const`
- L30 _public function_ `virtual float GetThickness() const`
- L31 _public function_ `virtual const FSlateBrush* GetBrush() const`
- L32 _public function_ `virtual const FText& GetToolTip() const`
- L33 _public function_ `virtual ESchematicGraphVisibility::Type GetVisibility() const`
- L34 _public function_ `virtual void SetVisibility(ESchematicGraphVisibility::Type InVisibility)`
- L38 _protected member_ `FSchematicGraphModel* Model = nullptr;`
- L39 _protected member_ `FGuid Guid = FGuid::NewGuid();`
- L40 _protected member_ `FGuid SourceNodeGuid = FGuid();`
- L41 _protected member_ `FGuid TargetNodeGuid = FGuid();`
- L42 _protected member_ `float Minimum = 0.f;`
- L43 _protected member_ `float Maximum = 1.f;`
- L44 _protected member_ `FVector2d SourceNodeOffset = FVector2d::ZeroVector;`
- L45 _protected member_ `FVector2d TargetNodeOffset = FVector2d::ZeroVector;`
- L46 _protected member_ `FLinearColor Color = FLinearColor::White;`
- L47 _protected member_ `float Thickness = 1.f;`
- L48 _protected member_ `const FSlateBrush* Brush = nullptr;`
- L49 _protected member_ `FText ToolTip = FText();`
- L50 _protected member_ `ESchematicGraphVisibility::Type Visibility = ESchematicGraphVisibility::Visible;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define SCHEMATICGRAPHLINK_BODY(ClassName, SuperClass) \`

### `Source/Editor/AnimationEditorWidgets/Public/SchematicGraphPanel/SchematicGraphModel.h` (Public)


#### class `FSchematicGraphModel`  
`class FSchematicGraphModel : public TSharedFromThis<FSchematicGraphModel>`  
_L13-300_
- inherits: `TSharedFromThis<FSchematicGraphModel>`
- L17 _public prototype_ `SCHEMATICGRAPHELEMENT_BODY_BASE(FSchematicGraphModel) virtual void Reset();`
- L20 _public function_ `virtual void ApplyToPanel(SSchematicGraphPanel* InPanel)`
- L23 _public function_ `template<typename NodeType = FSchematicGraphNode> NodeType* AddNode(bool bNotify = true)`
- L38 _public function_ `template<typename NodeType = FSchematicGraphNode> const NodeType* FindNode(const FGuid& InNodeGuid) const`
- L48 _public function_ `template<typename NodeType = FSchematicGraphNode> NodeType* FindNode(const FGuid& InNodeGuid)`
- L55 _public function_ `template<typename NodeType = FSchematicGraphNode> const NodeType* FindNodeChecked(const FGuid& InNodeGuid) const`
- L66 _public function_ `template<typename NodeType = FSchematicGraphNode> NodeType* FindNodeChecked(const FGuid& InNodeGuid)`
- L72 _public prototype_ `virtual bool RemoveNode(const FGuid& InNodeGuid);`
- L74 _public prototype_ `virtual bool SetParentNode(const FGuid& InChildNodeGuid, const FGuid& InParentNodeGuid, bool bUpdateGroupNode = true);`
- L75 _public prototype_ `virtual bool SetParentNode(const FSchematicGraphNode* InChildNode, const FSchematicGraphNode* InParentNode, bool bUpdateGroupNode = true);`
- L76 _public prototype_ `bool RemoveFromParentNode(const FGuid& InChildNodeGuid, bool bUpdateGroupNode = true);`
- L77 _public prototype_ `bool RemoveFromParentNode(const FSchematicGraphNode* InChildNode, bool bUpdateGroupNode = true);`
- L79 _public function_ `const TArray<TSharedPtr<FSchematicGraphNode>>& GetNodes() const`
- L81 _public prototype_ `FVector2d GetPositionForNode(const FGuid& InNodeGuid) const;`
- L82 _public prototype_ `virtual FVector2d GetPositionForNode(const FSchematicGraphNode* InNode) const;`
- L83 _public prototype_ `FVector2d GetPositionOffsetForNode(const FGuid& InNodeGuid) const;`
- L84 _public prototype_ `virtual FVector2d GetPositionOffsetForNode(const FSchematicGraphNode* InNode) const;`
- L85 _public prototype_ `bool GetPositionAnimationEnabledForNode(const FGuid& InNodeGuid) const;`
- L86 _public prototype_ `virtual bool GetPositionAnimationEnabledForNode(const FSchematicGraphNode* InNode) const;`
- L87 _public prototype_ `FVector2d GetSizeForNode(const FGuid& InNodeGuid) const;`
- L88 _public prototype_ `virtual FVector2d GetSizeForNode(const FSchematicGraphNode* InNode) const;`
- L89 _public prototype_ `float GetScaleForNode(const FGuid& InNodeGuid) const;`
- L90 _public prototype_ `virtual float GetScaleForNode(const FSchematicGraphNode* InNode) const;`
- L91 _public prototype_ `float GetScaleOffsetForNode(const FGuid& InNodeGuid) const;`
- L92 _public prototype_ `virtual float GetScaleOffsetForNode(const FSchematicGraphNode* InNode) const;`
- L93 _public prototype_ `float GetMinimumLinkDistanceForNode(const FGuid& InNodeGuid) const;`
- L94 _public prototype_ `virtual float GetMinimumLinkDistanceForNode(const FSchematicGraphNode* InNode) const;`
- L95 _public prototype_ `bool IsAutoScaleEnabledForNode(const FGuid& InNodeGuid) const;`
- L96 _public prototype_ `virtual bool IsAutoScaleEnabledForNode(const FSchematicGraphNode* InNode) const;`
- L97 _public prototype_ `int32 GetNumLayersForNode(const FGuid& InNodeGuid) const;`
- L98 _public prototype_ `virtual int32 GetNumLayersForNode(const FSchematicGraphNode* InNode) const;`
- L99 _public prototype_ `FLinearColor GetColorForNode(const FGuid& InNodeGuid, int32 InLayerIndex) const;`
- L100 _public prototype_ `virtual FLinearColor GetColorForNode(const FSchematicGraphNode* InNode, int32 InLayerIndex) const;`
- L101 _public prototype_ `const FSlateBrush* GetBrushForNode(const FGuid& InNodeGuid, int32 InLayerIndex) const;`
- L102 _public prototype_ `virtual const FSlateBrush* GetBrushForNode(const FSchematicGraphNode* InNode, int32 InLayerIndex) const;`
- L103 _public prototype_ `FText GetToolTipForNode(const FGuid& InNodeGuid) const;`
- L104 _public prototype_ `virtual FText GetToolTipForNode(const FSchematicGraphNode* InNode) const;`
- L105 _public prototype_ `ESchematicGraphVisibility::Type GetVisibilityForNode(const FGuid& InNodeGuid) const;`
- L106 _public prototype_ `virtual ESchematicGraphVisibility::Type GetVisibilityForNode(const FSchematicGraphNode* InNode) const;`
- L107 _public prototype_ `TOptional<ESchematicGraphVisibility::Type> GetVisibilityForChildNode(const FGuid& InParentNodeGuid, const FGuid& InChildNodeGuid) const;`
- L108 _public prototype_ `virtual TOptional<ESchematicGraphVisibility::Type> GetVisibilityForChildNode(const FSchematicGraphNode* InParentNode, const FSchematicGraphNode* InChildNode) const;`
- L109 _public prototype_ `TOptional<FVector2d> GetPositionForChildNode(const FGuid& InParentNodeGuid, const FGuid& InChildNodeGuid) const;`
- L110 _public prototype_ `virtual TOptional<FVector2d> GetPositionForChildNode(const FSchematicGraphNode* InParentNode, const FSchematicGraphNode* InChildNode) const;`
- L111 _public prototype_ `TOptional<float> GetScaleForChildNode(const FGuid& InParentNodeGuid, const FGuid& InChildNodeGuid) const;`
- L112 _public prototype_ `virtual TOptional<float> GetScaleForChildNode(const FSchematicGraphNode* InParentNode, const FSchematicGraphNode* InChildNode) const;`
- L113 _public prototype_ `TOptional<bool> GetInteractivityForChildNode(const FGuid& InParentNodeGuid, const FGuid& InChildNodeGuid) const;`
- L114 _public prototype_ `virtual TOptional<bool> GetInteractivityForChildNode(const FSchematicGraphNode* InParentNode, const FSchematicGraphNode* InChildNode) const;`
- L115 _public prototype_ `bool IsDragSupportedForNode(const FGuid& InNodeGuid) const;`
- L116 _public prototype_ `virtual bool IsDragSupportedForNode(const FSchematicGraphNode* InNode) const;`
- L117 _public prototype_ `virtual bool GetContextMenuForNode(const FSchematicGraphNode* InNode, FMenuBuilder& OutMenu) const;`
- L118 _public prototype_ `const TArray<TSharedPtr<FSchematicGraphNode>> GetSelectedNodes() const;`
- L119 _public prototype_ `void ClearSelection();`
- L121 _public prototype_ `FLinearColor GetBackgroundColorForTag(const FGuid& InNodeGuid, const FGuid& InTagGuid) const;`
- L122 _public prototype_ `virtual FLinearColor GetBackgroundColorForTag(const FSchematicGraphTag* InTag) const;`
- L123 _public prototype_ `FLinearColor GetForegroundColorForTag(const FGuid& InNodeGuid, const FGuid& InTagGuid) const;`
- L124 _public prototype_ `virtual FLinearColor GetForegroundColorForTag(const FSchematicGraphTag* InTag) const;`
- L125 _public prototype_ `FLinearColor GetLabelColorForTag(const FGuid& InNodeGuid, const FGuid& InTagGuid) const;`
- L126 _public prototype_ `virtual FLinearColor GetLabelColorForTag(const FSchematicGraphTag* InTag) const;`
- L127 _public prototype_ `const FSlateBrush* GetBackgroundBrushForTag(const FGuid& InNodeGuid, const FGuid& InTagGuid) const;`
- L128 _public prototype_ `virtual const FSlateBrush* GetBackgroundBrushForTag(const FSchematicGraphTag* InTag) const;`
- L129 _public prototype_ `const FSlateBrush* GetForegroundBrushForTag(const FGuid& InNodeGuid, const FGuid& InTagGuid) const;`
- L130 _public prototype_ `virtual const FSlateBrush* GetForegroundBrushForTag(const FSchematicGraphTag* InTag) const;`
- L131 _public prototype_ `const FText GetLabelForTag(const FGuid& InNodeGuid, const FGuid& InTagGuid) const;`
- L132 _public prototype_ `virtual const FText GetLabelForTag(const FSchematicGraphTag* InTag) const;`
- L133 _public prototype_ `const FText GetToolTipForTag(const FGuid& InNodeGuid, const FGuid& InTagGuid) const;`
- L134 _public prototype_ `virtual const FText GetToolTipForTag(const FSchematicGraphTag* InTag) const;`
- L135 _public prototype_ `ESchematicGraphVisibility::Type GetVisibilityForTag(const FGuid& InNodeGuid, const FGuid& InTagGuid) const;`
- L136 _public prototype_ `virtual ESchematicGraphVisibility::Type GetVisibilityForTag(const FSchematicGraphTag* InTag) const;`
- L139 _public function_ `template<typename LinkType = FSchematicGraphLink> LinkType* AddLink(const FGuid& InSourceNodeGuid, const FGuid& InTargetNodeGuid, bool bNotify = true)`
- L159 _public function_ `template<typename LinkType = FSchematicGraphLink> const LinkType* FindLink(const FGuid& InLinkGuid) const`
- L169 _public function_ `template<typename LinkType = FSchematicGraphLink> LinkType* FindLink(const FGuid& InLinkGuid)`
- L176 _public function_ `template<typename LinkType = FSchematicGraphLink> const LinkType* FindLinkChecked(const FGuid& InLinkGuid) const`
- L187 _public function_ `template<typename LinkType = FSchematicGraphLink> LinkType* FindLinkChecked(const FGuid& InLinkGuid)`
- L194 _public function_ `template<typename LinkType = FSchematicGraphLink> const LinkType* FindLink(const FGuid& InSourceNodeGuid, const FGuid& InTargetNodeGuid) const`
- L205 _public function_ `template<typename LinkType = FSchematicGraphLink> LinkType* FindLink(const FGuid& InSourceNodeGuid, const FGuid& InTargetNodeGuid)`
- L212 _public function_ `template<typename LinkType = FSchematicGraphLink> const LinkType* FindLinkChecked(const FGuid& InSourceNodeGuid, const FGuid& InTargetNodeGuid) const`
- L224 _public function_ `template<typename LinkType = FSchematicGraphLink> LinkType* FindLinkChecked(const FGuid& InSourceNodeGuid, const FGuid& InTargetNodeGuid)`
- L230 _public prototype_ `bool IsLinkedTo(const FGuid& InSourceNodeGuid, const FGuid& InTargetNodeGuid) const;`
- L231 _public prototype_ `TArray<const FSchematicGraphLink*> FindLinksOnNode(const FGuid& InNodeGuid) const;`
- L232 _public prototype_ `TArray<const FSchematicGraphLink*> FindLinksOnSource(const FGuid& InSourceNodeGuid) const;`
- L233 _public prototype_ `TArray<const FSchematicGraphLink*> FindLinksOnTarget(const FGuid& InTargetNodeGuid) const;`
- L235 _public prototype_ `virtual bool RemoveLink(const FGuid& InLinkGuid);`
- L237 _public function_ `const TArray<TSharedPtr<FSchematicGraphLink>>& GetLinks() const`
- L239 _public prototype_ `float GetMinimumForLink(const FGuid& InLinkGuid) const;`
- L240 _public prototype_ `virtual float GetMinimumForLink(const FSchematicGraphLink* InLink) const;`
- L241 _public prototype_ `float GetMaximumForLink(const FGuid& InLinkGuid) const;`
- L242 _public prototype_ `virtual float GetMaximumForLink(const FSchematicGraphLink* InLink) const;`
- L243 _public prototype_ `FVector2d GetSourceNodeOffsetForLink(const FGuid& InLinkGuid) const;`
- L244 _public prototype_ `FVector2d GetSourceNodeOffsetForLink(const FSchematicGraphLink* InLink) const;`
- L245 _public prototype_ `FVector2d GetTargetNodeOffsetForLink(const FGuid& InLinkGuid) const;`
- L246 _public prototype_ `FVector2d GetTargetNodeOffsetForLink(const FSchematicGraphLink* InLink) const;`
- L247 _public prototype_ `FLinearColor GetColorForLink(const FGuid& InLinkGuid) const;`
- L248 _public prototype_ `virtual FLinearColor GetColorForLink(const FSchematicGraphLink* InLink) const;`
- L249 _public prototype_ `float GetThicknessForLink(const FGuid& InLinkGuid) const;`
- L250 _public prototype_ `virtual float GetThicknessForLink(const FSchematicGraphLink* InLink) const;`
- L251 _public prototype_ `const FSlateBrush* GetBrushForLink(const FGuid& InLinkGuid) const;`
- L252 _public prototype_ `virtual const FSlateBrush* GetBrushForLink(const FSchematicGraphLink* InLink) const;`
- L253 _public prototype_ `const FText GetToolTipForLink(const FGuid& InLinkGuid) const;`
- L254 _public prototype_ `virtual const FText GetToolTipForLink(const FSchematicGraphLink* InLink) const;`
- L255 _public prototype_ `ESchematicGraphVisibility::Type GetVisibilityForLink(const FGuid& InLinkGuid) const;`
- L256 _public prototype_ `virtual ESchematicGraphVisibility::Type GetVisibilityForLink(const FSchematicGraphLink* InLink) const;`
- L258 _public function_ `virtual bool IsAutoGroupingEnabled() const`
- L259 _public function_ `virtual float GetAutoGroupingDistance() const`
- L260 _public prototype_ `virtual FSchematicGraphGroupNode* AddAutoGroupNode();`
- L262 _public function_ `FOnSchematicGraphNodeAdded& OnNodeAdded()`
- L263 _public function_ `FOnNodeRemoved& OnNodeRemoved()`
- L264 _public function_ `FOnSchematicGraphLinkAdded& OnLinkAdded()`
- L265 _public function_ `FOnLinkRemoved& OnLinkRemoved()`
- L266 _public function_ `FOnSchematicGraphTagAdded& OnTagAdded()`
- L267 _public function_ `FOnTagRemoved& OnTagRemoved()`
- L268 _public function_ `FOnGraphReset& OnGraphReset()`
- L270 _public function_ `virtual bool GetForwardedNodeForDrag(FGuid& InOutGuid) const`
- L272 _public prototype_ `const FSchematicGraphGroupNode* GetLastExpandedNode() const;`
- L273 _public prototype_ `virtual void SetLastExpandedNode(const FSchematicGraphGroupNode* InGroupNode);`
- L274 _public function_ `void ClearLastExpandedNode()`
- L279 _public prototype_ `virtual void Tick(float InDeltaTime);`
- L283 _protected member_ `TArray<TSharedPtr<FSchematicGraphNode>> Nodes;`
- L284 _protected member_ `TMap<FGuid, TSharedPtr<FSchematicGraphNode>> NodeByGuid;`
- L285 _protected member_ `TArray<TSharedPtr<FSchematicGraphLink>> Links;`
- L286 _protected member_ `TMap<FGuid, TSharedPtr<FSchematicGraphLink>> LinkByGuid;`
- L287 _protected member_ `TMap<uint32, TSharedPtr<FSchematicGraphLink>> LinkByHash;`
- L288 _protected member_ `TMap<FGuid, TTuple<TArray<FGuid>, TArray<FGuid>>> NodeGuidToLinkGuids;`
- L289 _protected member_ `FGuid LastExpandedNode = FGuid();`
- L291 _protected member_ `FOnSchematicGraphNodeAdded OnNodeAddedDelegate;`
- L292 _protected member_ `FOnNodeRemoved OnNodeRemovedDelegate;`
- L293 _protected member_ `FOnSchematicGraphLinkAdded OnLinkAddedDelegate;`
- L294 _protected member_ `FOnLinkRemoved OnLinkRemovedDelegate;`
- L295 _protected member_ `FOnSchematicGraphTagAdded OnTagAddedDelegate;`
- L296 _protected member_ `FOnTagRemoved OnTagRemovedDelegate;`
- L297 _protected member_ `FOnGraphReset OnGraphResetDelegate;`

### `Source/Editor/AnimationEditorWidgets/Public/SchematicGraphPanel/SchematicGraphNode.h` (Public)


#### class `FSchematicGraphNode`  
`class FSchematicGraphNode : public TSharedFromThis<FSchematicGraphNode>`  
_L16-167_
- inherits: `TSharedFromThis<FSchematicGraphNode>`
- L22 _public prototype_ `FSchematicGraphNode();`
- L24 _public function_ `const FGuid& GetGuid() const`
- L25 _public function_ `const FSchematicGraphModel* GetGraph() const`
- L26 _public function_ `bool HasParentNode() const`
- L27 _public function_ `const FGuid& GetParentNodeGuid() const`
- L28 _public prototype_ `const FSchematicGraphNode* GetParentNode() const;`
- L29 _public prototype_ `FSchematicGraphNode* GetParentNode();`
- L30 _public prototype_ `const FGuid& GetRootNodeGuid() const;`
- L31 _public prototype_ `const FSchematicGraphNode* GetRootNode() const;`
- L32 _public prototype_ `FSchematicGraphNode* GetRootNode();`
- L33 _public function_ `bool IsRootNode() const`
- L34 _public prototype_ `FSchematicGraphGroupNode* GetGroupNode();`
- L35 _public prototype_ `const FSchematicGraphGroupNode* GetGroupNode() const;`
- L36 _public function_ `int32 GetNumChildNodes() const`
- L37 _public function_ `const TArray<FGuid>& GetChildNodeGuids() const`
- L38 _public prototype_ `const FSchematicGraphNode* GetChildNode(int32 InChildNodeIndex) const;`
- L39 _public prototype_ `FSchematicGraphNode* GetChildNode(int32 InChildNodeIndex);`
- L40 _public prototype_ `TOptional<ESchematicGraphVisibility::Type> GetVisibilityForChildNode(const FGuid& InChildGuid) const;`
- L41 _public function_ `virtual TOptional<ESchematicGraphVisibility::Type> GetVisibilityForChildNode(const FSchematicGraphNode* InChildNode) const`
- L42 _public prototype_ `TOptional<FVector2d> GetPositionForChildNode(const FGuid& InChildGuid) const;`
- L43 _public function_ `virtual TOptional<FVector2d> GetPositionForChildNode(const FSchematicGraphNode* InChildNode) const`
- L44 _public prototype_ `TOptional<float> GetScaleForChildNode(const FGuid& InChildGuid) const;`
- L45 _public function_ `virtual TOptional<float> GetScaleForChildNode(const FSchematicGraphNode* InChildNode) const`
- L46 _public prototype_ `TOptional<bool> GetInteractivityForChildNode(const FGuid& InChildGuid) const;`
- L47 _public function_ `virtual TOptional<bool> GetInteractivityForChildNode(const FSchematicGraphNode* InChildNode) const`
- L48 _public function_ `bool IsSelected() const`
- L49 _public function_ `void SetSelected(bool bSelected = true)`
- L50 _public function_ `virtual const FText& GetLabel() const`
- L51 _public function_ `void SetLabel(const FText& InLabel)`
- L52 _public prototype_ `virtual FVector2d GetPosition() const;`
- L53 _public function_ `virtual void SetPosition(const FVector2d& InPosition)`
- L54 _public function_ `virtual FVector2d GetPositionOffset() const`
- L55 _public function_ `virtual void SetPositionOffset(const FVector2d& InPositionOffset)`
- L56 _public function_ `virtual float GetScaleOffset() const`
- L57 _public function_ `virtual void SetScaleOffset(float InScaleOffset)`
- L58 _public function_ `int32 GetNumLayers() const`
- L59 _public function_ `virtual FLinearColor GetColor(int32 InLayerIndex) const`
- L60 _public function_ `virtual const FSlateBrush* GetBrush(int32 InLayerIndex) const`
- L61 _public function_ `virtual bool IsAutoScaleEnabled() const`
- L62 _public prototype_ `virtual const FText& GetToolTip() const;`
- L63 _public prototype_ `virtual ESchematicGraphVisibility::Type GetVisibility() const;`
- L64 _public function_ `virtual void SetVisibility(ESchematicGraphVisibility::Type InVisibility)`
- L65 _public prototype_ `virtual bool IsInteractive() const;`
- L66 _public function_ `virtual bool IsDragSupported() const`
- L67 _public function_ `virtual void SetDragSupported(bool InDragSupported)`
- L69 _public prototype_ `virtual FReply OnClicked(const FPointerEvent& InMouseEvent);`
- L70 _public prototype_ `virtual void OnMouseEnter();`
- L71 _public prototype_ `virtual void OnMouseLeave();`
- L72 _public prototype_ `virtual void OnDragOver();`
- L73 _public prototype_ `virtual void OnDragLeave();`
- L75 _public prototype_ `virtual FString GetDragDropDecoratorLabel() const;`
- L78 _public function_ `template<typename TagType = FSchematicGraphTag> TagType* AddTag(bool bNotify = true)`
- L93 _public function_ `template<typename TagType = FSchematicGraphTag> const TagType* FindTag(const FGuid& InTagGuid = FGuid()) const`
- L113 _public function_ `template<typename TagType = FSchematicGraphTag> TagType* FindTag(const FGuid& InTagGuid = FGuid())`
- L120 _public function_ `template<typename TagType = FSchematicGraphTag> const TagType* FindTagChecked(const FGuid& InTagGuid) const`
- L131 _public function_ `template<typename TagType = FSchematicGraphTag> TagType* FindTagChecked(const FGuid& InTagGuid)`
- L137 _public prototype_ `virtual bool RemoveTag(const FGuid& InTagGuid);`
- L139 _public function_ `const TArray<TSharedPtr<FSchematicGraphTag>>& GetTags() const`
- L143 _protected prototype_ `void NotifyTagAdded(const TSharedPtr<FSchematicGraphTag>& Tag);`
- L145 _protected member_ `FSchematicGraphModel* Model = nullptr;`
- L146 _protected member_ `FGuid Guid = FGuid::NewGuid();`
- L147 _protected member_ `FText Label = FText();`
- L148 _protected member_ `FGuid ParentNodeGuid = FGuid();`
- L149 _protected member_ `TArray<FGuid> ChildNodeGuids;`
- L150 _protected member_ `bool bIsSelected = false;`
- L151 _protected member_ `FVector2d Position = FVector2d::ZeroVector;`
- L152 _protected member_ `FVector2d PositionOffset = FVector2d::ZeroVector;`
- L153 _protected member_ `float ScaleOffset = 1.f;`
- L154 _protected member_ `TArray<FLinearColor> Colors;`
- L155 _protected member_ `TArray<const FSlateBrush*> Brushes;`
- L156 _protected member_ `FText ToolTip = FText();`
- L157 _protected member_ `ESchematicGraphVisibility::Type Visibility = ESchematicGraphVisibility::Visible;`
- L158 _protected member_ `bool bDragSupported = false;`
- L160 _protected member_ `static inline constexpr float ScaledUp = 1.25;`
- L161 _protected member_ `static inline constexpr float ScaledDown = 0.75;`
- L163 _protected member_ `TArray<TSharedPtr<FSchematicGraphTag>> Tags;`
- L164 _protected member_ `TMap<FGuid, TSharedPtr<FSchematicGraphTag>> TagByGuid;`

#### class `FSchematicGraphGroupNode`  
`class FSchematicGraphGroupNode : public FSchematicGraphNode`  
_L169-213_
- inherits: `FSchematicGraphNode`
- L173 _public prototype_ `SCHEMATICGRAPHNODE_BODY(FSchematicGraphGroupNode, FSchematicGraphNode) FSchematicGraphGroupNode();`
- L176 _public prototype_ `virtual ~FSchematicGraphGroupNode() override = default;`
- L179 _public prototype_ `virtual TOptional<ESchematicGraphVisibility::Type> GetVisibilityForChildNode(const FSchematicGraphNode* InChildNode) const override;` — FSchematicGraphNode interface
- L180 _public prototype_ `virtual TOptional<FVector2d> GetPositionForChildNode(const FSchematicGraphNode* InChildNode) const override;`
- L181 _public prototype_ `virtual TOptional<float> GetScaleForChildNode(const FSchematicGraphNode* InChildNode) const override;`
- L182 _public prototype_ `virtual TOptional<bool> GetInteractivityForChildNode(const FSchematicGraphNode* InChildNode) const override;`
- L183 _public prototype_ `virtual FReply OnClicked(const FPointerEvent& InMouseEvent) override;`
- L184 _public prototype_ `virtual void OnDragOver() override;`
- L185 _public prototype_ `virtual void OnDragLeave() override;`
- L187 _public prototype_ `bool IsExpanded() const;`
- L188 _public prototype_ `bool IsExpanding() const;`
- L189 _public prototype_ `bool IsCollapsing() const;`
- L190 _public prototype_ `float GetExpansionState() const;`
- L191 _public prototype_ `void SetExpanded(bool InExpanded, bool bAutoCloseParentGroups = false);`
- L192 _public function_ `FLinearColor GetExpansionColor() const`
- L193 _public function_ `void SetExpansionColor(FLinearColor InExpansionColor)`
- L194 _public function_ `float GetExpansionRadius() const`
- L195 _public function_ `void SetExpansionRadius(float InExpansionRadius)`
- L196 _public prototype_ `float GetDelayDuration(bool bEnter) const;`
- L197 _public function_ `void SetDelayDuration(bool bEnter, float InDelayDuration)`
- L201 _protected function_ `const TEasingAttributeInterpolator<float>::FSettings& GetAnimationSettings() const`
- L202 _protected prototype_ `void SetAnimationSettings(const TEasingAttributeInterpolator<float>::FSettings& InSettings);`
- L204 _protected member_ `float ExpansionRadius = 60.f;`
- L205 _protected member_ `FLinearColor ExpansionColor = FLinearColor::White * FLinearColor(1.f, 1.f, 1.f, 0.5f);`
- L206 _protected member_ `float EnterDelayDuration = 0.25f;`
- L207 _protected member_ `float LeaveDelayDuration = 0.75f;`
- L208 _protected member_ `TOptional<bool> LastExpansionState;`
- L209 _protected member_ `TEasingAttributeInterpolator<float>::FSettings AnimationSettings;`
- L210 _protected member_ `TSharedPtr<TAnimatedAttribute<float>> ExpansionState;`

#### class `FSchematicGraphAutoGroupNode`  
`class FSchematicGraphAutoGroupNode : public FSchematicGraphGroupNode`  
_L215-226_
- inherits: `FSchematicGraphGroupNode`
- L219 _public prototype_ `SCHEMATICGRAPHNODE_BODY(FSchematicGraphAutoGroupNode, FSchematicGraphGroupNode) virtual const FText& GetLabel() const override;`
- L225 _protected member_ `mutable FText AutoGroupLabel;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define SCHEMATICGRAPHNODE_BODY(ClassName, SuperClass) \`

### `Source/Editor/AnimationEditorWidgets/Public/SchematicGraphPanel/SchematicGraphStyle.h` (Public)


#### class `FSchematicGraphStyle`  
`class FSchematicGraphStyle final : public FSlateStyleSet`  
_L13-54_
- inherits: `FSlateStyleSet`
- L18 _public function_ `FSchematicGraphStyle() : FSlateStyleSet("SchematicGraphStyle")`
- L48 _public prototype_ `static FSchematicGraphStyle& Get();`
- L50 _public function_ `~FSchematicGraphStyle()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANIMATIONEDITORWIDGETS_API`

### `Source/Editor/AnimationEditorWidgets/Public/SchematicGraphPanel/SchematicGraphTag.h` (Public)


#### class `FSchematicGraphTag`  
`class FSchematicGraphTag : public TSharedFromThis<FSchematicGraphTag>`  
_L11-56_
- inherits: `TSharedFromThis<FSchematicGraphTag>`
- L17 _public prototype_ `FSchematicGraphTag();`
- L19 _public prototype_ `const FSchematicGraphNode* GetNode() const;`
- L20 _public function_ `const FGuid& GetGuid() const`
- L21 _public function_ `virtual FLinearColor GetBackgroundColor() const`
- L22 _public function_ `virtual void SetBackgroundColor(const FLinearColor& InBackgroundColor)`
- L23 _public function_ `virtual FLinearColor GetForegroundColor() const`
- L24 _public function_ `virtual void SetForegroundColor(const FLinearColor& InForegroundColor)`
- L25 _public function_ `virtual FLinearColor GetLabelColor() const`
- L26 _public function_ `virtual void SetLabelColor(const FLinearColor& InLabelColor)`
- L27 _public function_ `virtual const FSlateBrush* GetBackgroundBrush() const`
- L28 _public function_ `virtual void SetBackgroundBrush(const FSlateBrush* InBackgroundBrush)`
- L29 _public function_ `virtual const FSlateBrush* GetForegroundBrush() const`
- L30 _public function_ `virtual void SetForegroundBrush(const FSlateBrush* InForegroundBrush)`
- L31 _public function_ `virtual FText GetLabel() const`
- L32 _public function_ `virtual void SetLabel(const FText& InLabel)`
- L33 _public function_ `virtual FText GetToolTip() const`
- L34 _public function_ `virtual void SetToolTip(const FText& InToolTip)`
- L35 _public function_ `virtual float GetPlacementAngle() const`
- L36 _public function_ `virtual void SetPlacementAngle(float InPlacementAngle)`
- L37 _public function_ `virtual ESchematicGraphVisibility::Type GetVisibility() const`
- L38 _public function_ `virtual void SetVisibility(ESchematicGraphVisibility::Type InVisibility)`
- L42 _protected member_ `FSchematicGraphNode* Node = nullptr;`
- L43 _protected member_ `FGuid Guid = FGuid::NewGuid();`
- L44 _protected member_ `FLinearColor BackgroundColor = FLinearColor(FColor(0, 112, 224));`
- L45 _protected member_ `FLinearColor ForegroundColor = FLinearColor::White;`
- L46 _protected member_ `FLinearColor LabelColor = FLinearColor::White;`
- L47 _protected member_ `const FSlateBrush* BackgroundBrush = nullptr;`
- L48 _protected member_ `const FSlateBrush* ForegroundBrush = nullptr;`
- L49 _protected member_ `FText Label = FText();`
- L50 _protected member_ `FText ToolTip = FText();`
- L51 _protected member_ `float PlacementAngle = -45.f;`
- L52 _protected member_ `ESchematicGraphVisibility::Type Visibility = ESchematicGraphVisibility::Visible;`

#### class `FSchematicGraphGroupTag`  
`class FSchematicGraphGroupTag : public FSchematicGraphTag`  
_L58-68_
- inherits: `FSchematicGraphTag`
- L62 _public prototype_ `SCHEMATICGRAPHTAG_BODY(FSchematicGraphGroupTag, FSchematicGraphTag) virtual ~FSchematicGraphGroupTag() override = default;`
- L66 _public prototype_ `virtual ESchematicGraphVisibility::Type GetVisibility() const override;`
- L67 _public prototype_ `virtual FText GetLabel() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define SCHEMATICGRAPHTAG_BODY(ClassName, SuperClass) \`

### `Source/Editor/AnimationEditorWidgets/Public/SchematicGraphPanel/SchematicViewportTabSummoner.h` (Public)


#### struct `FSchematicViewportArgs`  
`struct FSchematicViewportArgs`  
_L14-24_
- desc: Arguments used to create a persona viewport tab
- L16 _public function_ `FSchematicViewportArgs()`
- L20 _public member_ `TWeakPtr<FSchematicGraphModel> SchematicGraphWeak;` — The model which contains the graph to display
- L23 _public member_ `FOnSchematicViewportCreated OnViewportCreated;` — Delegate fired when the viewport is created

#### struct `FSchematicViewportTabSummoner`  
`struct FSchematicViewportTabSummoner : public FWorkflowTabFactory`  
_L27-40_
- inherits: `FWorkflowTabFactory`
- L30 _public member_ `static const FName TabID;`
- L33 _public prototype_ `FSchematicViewportTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const FSchematicViewportArgs& InArgs);`
- L35 _public prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(TSharedRef<FTabManager> TabManager, const FApplicationMode* CurrentApplicationMode) const;`
- L36 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L38 _public member_ `TWeakPtr<FSchematicGraphModel> SchematicGraphWeak;`
- L39 _public member_ `FOnSchematicViewportCreated OnViewportCreated;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSchematicViewportCreated, const TSharedRef<class SSchematicGraphPanel>&);` — Called back when a viewport is created
- L11 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSchematicViewportCreated, const TSharedRef<class SSchematicGraphPanel>&);` — Called back when a viewport is created
