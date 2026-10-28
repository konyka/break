# Plugins / TechAudioToolsMetaSound

- module root: `Plugins/Experimental/TechAudioTools/Source/TechAudioToolsMetaSound`
- headers: 4; symbols: 220
- symbol kinds: class=16, function=43, macro=3, member=46, namespace=2, prototype=110
- PrivateDependencyModuleNames: AudioExtensions, CoreUObject, Engine, Slate, UMG
- PublicDependencyModuleNames: Core, MetasoundEngine, MetasoundFrontend, ModelViewViewModel, SlateCore, TechAudioTools

### `Plugins/Experimental/TechAudioTools/Source/TechAudioToolsMetaSound/Public/Interfaces/MetaSoundLiteralInterface.h` (Public)


#### class `UMetaSoundLiteralWidgetInterface`  
`class UMetaSoundLiteralWidgetInterface : public UInterface`  
_L30-33_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable, DisplayName = "MetaSound Literal Widget Interface")`
- inherits: `UInterface`
- desc: Used for retrieving specific viewmodels from a MetaSoundViewModel, such as inputs or outputs. Simplifies the process of initializing MetaSound Literal Widgets by allowing the owning widget to call functions on entire containers of widgets that implement this interface, rather than painstakingly initializing each widget one-by-one. Widgets implementing this interface are expected to provide an array of input names in order to request the required InputViewModels from the owning widget's MetaSoundViewModel. Then, the widget can implement SetInputViewModels to correctly assign each InputViewModel received. To assign viewmodels, it is recommended to use either UMVVMView::SetViewModelByClass (if there aren't multiple viewmodels of the same class) or UMVVMView::SetViewModel (if there are multiple viewmodels of the same class). If using UMVVMView::SetViewModel, you must ensure the name of the viewmodel passed into the function matches the name of the corresponding viewmodel instance *exactly* or else the assignment will fail. It is recommended to expose a name variable to designers rather than hardcode a name value. @see UMetaSoundLiteralWidget_Float for an example implementation.

#### class `IMetaSoundLiteralWidgetInterface`  
`class IMetaSoundLiteralWidgetInterface`  
_L35-49_
- L42 _public prototype_ `TArray<FName> GetInputViewModelNames() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName = "Get Input Viewmodel Names", Category = "MetaSound Literal")` — Returns an array containing the names of the MetaSound Input Viewmodels required for this widget.
- L43 _public function_ `virtual TArray<FName> GetInputViewModelNames_Implementation() const`
- L47 _public prototype_ `void SetInputViewModels(UPARAM(DisplayName = "Input Viewmodels") const TMap<FName, UMetaSoundInputViewModel*>& I` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName = "Set Input Viewmodels", Category = "MetaSound Literal")` — Sets the MetaSound input viewmodels this widget binds to.
- L48 _public function_ `virtual void SetInputViewModels_Implementation(const TMap<FName, UMetaSoundInputViewModel*>& InputViewModels)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TECHAUDIOTOOLSMETASOUND_API`

### `Plugins/Experimental/TechAudioTools/Source/TechAudioToolsMetaSound/Public/ViewModels/MetaSoundLiteralViewModel.h` (Public)


#### class `UMetaSoundLiteralViewModel_Boolean`  
`class UMetaSoundLiteralViewModel_Boolean : public UMVVMViewModelBase`  
_L20-45_
- reflection: `UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "MetaSound Literal Boolean Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for binding a boolean-type MetaSound Literal with a widget.
- L27 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Setter, Category = "Boolean Literal", meta = (AllowPrivateAccess))` — The bound MetaSound Literal value. Should be bound using a two-way binding with the Literal variable of a MetaSoundInputViewModel.
- L31 _protected member_ `bool SourceValue = false;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Boolean Literal", meta = (AllowPrivateAccess))` — The value of the bound Literal as a bool.
- L34 _public function_ `const FMetasoundFrontendLiteral& GetLiteral() const`
- L35 _public function_ `bool GetSourceValue() const`
- L37 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L38 _public prototype_ `void SetSourceValue(bool InSourceValue);`
- L40 _public prototype_ `virtual void PostInitProperties() override;`
- L43 _public prototype_ `virtual void PostEditUndo() override;`

#### class `UMetaSoundLiteralViewModel_BooleanArray`  
`class UMetaSoundLiteralViewModel_BooleanArray : public UMVVMViewModelBase`  
_L51-76_
- reflection: `UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "MetaSound Literal Boolean Array Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for binding a boolean array-type MetaSound Literal with a widget.
- L58 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Setter, Category = "Boolean Array Literal", meta = (AllowPrivateAccess))` — The bound MetaSound Literal value. Should be bound using a two-way binding with the Literal variable of a MetaSoundInputViewModel.
- L62 _protected member_ `TArray<bool> SourceValue;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Boolean Array Literal", meta = (AllowPrivateAccess))` — The value of the bound Literal as a boolean array.
- L65 _public function_ `const FMetasoundFrontendLiteral& GetLiteral() const`
- L66 _public function_ `TArray<bool> GetSourceValue() const`
- L68 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L69 _public prototype_ `void SetSourceValue(const TArray<bool>& InSourceValue);`
- L71 _public prototype_ `virtual void PostInitProperties() override;`
- L74 _public prototype_ `virtual void PostEditUndo() override;`

#### class `UMetaSoundLiteralViewModel_Integer`  
`class UMetaSoundLiteralViewModel_Integer : public UMVVMViewModelBase`  
_L82-123_
- reflection: `UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "MetaSound Literal Integer Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for binding an integer-type MetaSound Literal with a widget.
- L89 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Setter, Category = "Integer Literal", meta = (AllowPrivateAccess))` — The bound MetaSound Literal value. Should be bound using a two-way binding with the Literal variable of a MetaSoundInputViewModel.
- L93 _protected member_ `int32 SourceValue = 0;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Integer Literal", meta = (AllowPrivateAccess))` — The value of the bound Literal as an integer.
- L97 _protected member_ `float NormalizedValue = 0.f;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Integer Literal", meta = (AllowPrivateAccess))` — The SourceValue normalized to a 0-1 range based on the set Range values. Used for UI like sliders and knobs that use a normalized range.
- L101 _protected member_ `FInt32Range Range;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, FieldNotify, Category = "Integer Literal", meta = (AllowPrivateAccess))` — Sets the min and max values of the UI range. Range bounds should be closed (either Inclusive or Exclusive) and not open.
- L105 _public prototype_ `float GetStepSize() const;` — `UFUNCTION(BlueprintCallable, FieldNotify, Category = "Integer Literal")`
- L107 _public function_ `const FMetasoundFrontendLiteral& GetLiteral() const`
- L108 _public function_ `int32 GetSourceValue() const`
- L109 _public function_ `float GetNormalizedValue() const`
- L111 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L112 _public prototype_ `void SetSourceValue(int32 InSourceValue);`
- L113 _public prototype_ `void SetNormalizedValue(float InNormalizedValue);`
- L115 _public prototype_ `virtual void PostInitProperties() override;`
- L118 _public prototype_ `virtual void PostEditUndo() override;`
- L122 _private member_ `bool bIsUpdating = false;`

#### class `UMetaSoundLiteralViewModel_IntegerArray`  
`class UMetaSoundLiteralViewModel_IntegerArray : public UMVVMViewModelBase`  
_L129-154_
- reflection: `UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "MetaSound Literal Integer Array Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for binding an integer array-type MetaSound Literal with a widget.
- L136 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Setter, Category = "Integer Array Literal", meta = (AllowPrivateAccess))` — The bound MetaSound Literal value. Should be bound using a two-way binding with the Literal variable of a MetaSoundInputViewModel.
- L140 _protected member_ `TArray<int32> SourceValue;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Integer Array Literal", meta = (AllowPrivateAccess))` — The value of the bound Literal as an integer array.
- L143 _public function_ `const FMetasoundFrontendLiteral& GetLiteral() const`
- L144 _public function_ `TArray<int32> GetSourceValue() const`
- L146 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L147 _public prototype_ `void SetSourceValue(const TArray<int32>& InSourceValue);`
- L149 _public prototype_ `virtual void PostInitProperties() override;`
- L152 _public prototype_ `virtual void PostEditUndo() override;`

#### class `UMetaSoundLiteralViewModel_Float`  
`class UMetaSoundLiteralViewModel_Float : public UMVVMViewModelBase`  
_L173-252_
- reflection: `UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "MetaSound Literal Float Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for converting a float-type MetaSound Literal between Source, Normalized, and Display values. Source values refer to the units or range expected by the MetaSound Literal. Display values refer to a configurable conversion of the Source value. For instance, a "Volume" input might expect a linear gain value in the MetaSound, but users may wish to display the value as decibels. The Normalized value is to be used for UI elements such as sliders and knobs. The Literal variable belonging to this viewmodel is expected to be bound to the Literal variable of a MetaSoundInputViewModel using a two-way binding for bidirectional updates. Doing so will ensure all updates to the input in the MetaSound Editor are reflected in your widget and vice versa. This viewmodel should most likely use the Create Instance setting, along with the Expose Instance in Editor option. This allows designers to easily configure units and range settings in the Details panel of instances of the owning widget. @see UTechAudioToolsFloatMapping for unit conversion and range mapping logic.
- L180 _protected member_ `bool bShowDisplayValues = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, FieldNotify, Getter = "IsShowingDisplayValues", Setter = "SetShowDisplayValues", Category = "Float Literal")` — If true, the NormalizedValue will be mapped to the DisplayRange, else mapped to the SourceRange.
- L184 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Setter, Category = "Float Literal", meta = (AllowPrivateAccess))` — The bound MetaSound Literal value. Should be bound using a two-way binding with the Literal variable of a MetaSoundInputViewModel.
- L188 _protected member_ `float SourceValue = 0.f;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Float Literal", meta = (AllowPrivateAccess))` — The value of the bound Literal as a float.
- L195 _protected member_ `float NormalizedValue = 0.f;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Float Literal", meta = (AllowPrivateAccess))` — The normalized (0-1) representation of the value currently surfaced to the UI. If bShowDisplayValues is true, this is DisplayValue mapped into 0-1 space. Otherwise, it's SourceValue mapped into 0-1 space. Used by knobs/sliders purely for visual feedback.
- L199 _protected member_ `float DisplayValue = 0.f;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Float Literal", meta = (AllowPrivateAccess))` — The user-facing display value (e.g. dB, Hz, semitones). Can be modified and is automatically converted to the expected SourceRange.
- L203 _protected member_ `TObjectPtr<UTechAudioToolsFloatMapping> RangeValues;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Float Range Settings", meta = (AllowPrivateAccess))` — Mapping pair used to convert between float literal, normalized, and display values.
- L208 _public prototype_ `float GetSourceRangeMin() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, FieldNotify, Category = "TechAudioTools")` — Returns the range minimum of the SourceRange.
- L212 _public prototype_ `float GetSourceRangeMax() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, FieldNotify, Category = "TechAudioTools")` — Returns the range maximum of the SourceRange.
- L216 _public prototype_ `ETechAudioToolsFloatUnit GetSourceUnits() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, FieldNotify, Category = "TechAudioTools")` — Returns the units associated with the SourceValue.
- L220 _public prototype_ `float GetDisplayRangeMin() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, FieldNotify, Category = "TechAudioTools")` — Returns the range minimum of the DisplayRange.
- L224 _public prototype_ `float GetDisplayRangeMax() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, FieldNotify, Category = "TechAudioTools")` — Returns the range maximum of the DisplayRange.
- L228 _public prototype_ `ETechAudioToolsFloatUnit GetDisplayUnits() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, FieldNotify, Category = "TechAudioTools")` — Returns the units associated with the DisplayValue.
- L230 _public prototype_ `explicit UMetaSoundLiteralViewModel_Float(const FObjectInitializer& ObjectInitializer);`
- L232 _public function_ `bool IsShowingDisplayValues() const`
- L233 _public function_ `const FMetasoundFrontendLiteral& GetLiteral() const`
- L234 _public function_ `float GetSourceValue() const`
- L235 _public function_ `float GetNormalizedValue() const`
- L236 _public function_ `float GetDisplayValue() const`
- L238 _public prototype_ `void SetShowDisplayValues(bool bInIsShowingDisplayValues);`
- L239 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L240 _public prototype_ `void SetSourceValue(float InSourceValue);`
- L241 _public prototype_ `void SetNormalizedValue(float InNormalizedValue);`
- L242 _public prototype_ `void SetDisplayValue(float InDisplayValue);`
- L244 _public prototype_ `virtual void PostInitProperties() override;`
- L247 _public prototype_ `virtual void PostEditUndo() override;`
- L251 _private member_ `bool bIsUpdating = false;`

#### class `UMetaSoundLiteralViewModel_FloatArray`  
`class UMetaSoundLiteralViewModel_FloatArray : public UMVVMViewModelBase`  
_L258-283_
- reflection: `UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "MetaSound Literal Float Array Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for binding a float array-type MetaSound Literal with a widget.
- L265 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Setter, Category = "Float Array Literal", meta = (AllowPrivateAccess))` — The bound MetaSound Literal value. Should be bound using a two-way binding with the Literal variable of a MetaSoundInputViewModel.
- L269 _protected member_ `TArray<float> SourceValue;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Float Array Literal", meta = (AllowPrivateAccess))` — The value of the bound Literal as a float array.
- L272 _public function_ `const FMetasoundFrontendLiteral& GetLiteral() const`
- L273 _public function_ `TArray<float> GetSourceValue() const`
- L275 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L276 _public prototype_ `void SetSourceValue(const TArray<float>& InSourceValue);`
- L278 _public prototype_ `virtual void PostInitProperties() override;`
- L281 _public prototype_ `virtual void PostEditUndo() override;`

#### class `UMetaSoundLiteralViewModel_String`  
`class UMetaSoundLiteralViewModel_String : public UMVVMViewModelBase`  
_L289-314_
- reflection: `UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "MetaSound Literal String Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for binding a string-type MetaSound Literal with a widget.
- L296 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Setter, Category = "String Literal", meta = (AllowPrivateAccess))` — The bound MetaSound Literal value. Should be bound using a two-way binding with the Literal variable of a MetaSoundInputViewModel.
- L300 _protected member_ `FString SourceValue;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "String Literal", meta = (AllowPrivateAccess))` — The value of the bound Literal as a string.
- L303 _public function_ `const FMetasoundFrontendLiteral& GetLiteral() const`
- L304 _public function_ `FString GetSourceValue() const`
- L306 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L307 _public prototype_ `void SetSourceValue(const FString& InSourceValue);`
- L309 _public prototype_ `virtual void PostInitProperties() override;`
- L312 _public prototype_ `virtual void PostEditUndo() override;`

#### class `UMetaSoundLiteralViewModel_StringArray`  
`class UMetaSoundLiteralViewModel_StringArray : public UMVVMViewModelBase`  
_L320-345_
- reflection: `UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "MetaSound Literal String Array Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for binding a string array-type MetaSound Literal with a widget.
- L327 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Setter, Category = "String Array Literal", meta = (AllowPrivateAccess))` — The bound MetaSound Literal value. Should be bound using a two-way binding with the Literal variable of a MetaSoundInputViewModel.
- L331 _protected member_ `TArray<FString> SourceValue;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "String Array Literal", meta = (AllowPrivateAccess))` — The value of the bound Literal as a string array.
- L334 _public function_ `const FMetasoundFrontendLiteral& GetLiteral() const`
- L335 _public function_ `TArray<FString> GetSourceValue() const`
- L337 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L338 _public prototype_ `void SetSourceValue(const TArray<FString>& InSourceValue);`
- L340 _public prototype_ `virtual void PostInitProperties() override;`
- L343 _public prototype_ `virtual void PostEditUndo() override;`

#### class `UMetaSoundLiteralViewModel_Object`  
`class UMetaSoundLiteralViewModel_Object : public UMVVMViewModelBase`  
_L351-376_
- reflection: `UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "MetaSound Literal Object Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for binding an object-type MetaSound Literal with a widget.
- L358 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Setter, Category = "Object Literal", meta = (AllowPrivateAccess))` — The bound MetaSound Literal value. Should be bound using a two-way binding with the Literal variable of a MetaSoundInputViewModel.
- L362 _protected member_ `TObjectPtr<UObject> SourceValue;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Object Literal", meta = (AllowPrivateAccess))` — The value of the bound Literal as an object.
- L365 _public function_ `const FMetasoundFrontendLiteral& GetLiteral() const`
- L366 _public function_ `UObject* GetSourceValue() const`
- L368 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L369 _public prototype_ `void SetSourceValue(UObject* InSourceValue);`
- L371 _public prototype_ `virtual void PostInitProperties() override;`
- L374 _public prototype_ `virtual void PostEditUndo() override;`

#### class `UMetaSoundLiteralViewModel_ObjectArray`  
`class UMetaSoundLiteralViewModel_ObjectArray : public UMVVMViewModelBase`  
_L382-407_
- reflection: `UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "MetaSound Literal Object Array Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for binding an object array-type MetaSound Literal with a widget.
- L389 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Setter, Category = "Object Array Literal", meta = (AllowPrivateAccess))` — The bound MetaSound Literal value. Should be bound using a two-way binding with the Literal variable of a MetaSoundInputViewModel.
- L393 _protected member_ `TArray<TObjectPtr<UObject>> SourceValue;` — `UPROPERTY(BlueprintReadWrite, Transient, FieldNotify, Getter, Setter, Category = "Object Array Literal", meta = (AllowPrivateAccess))` — The value of the bound Literal as an object array.
- L396 _public function_ `const FMetasoundFrontendLiteral& GetLiteral() const`
- L397 _public function_ `TArray<TObjectPtr<UObject>> GetSourceValue() const`
- L399 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L400 _public prototype_ `void SetSourceValue(const TArray<TObjectPtr<UObject>>& InSourceValue);`
- L402 _public prototype_ `virtual void PostInitProperties() override;`
- L405 _public prototype_ `virtual void PostEditUndo() override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TECHAUDIOTOOLSMETASOUND_API`

### `Plugins/Experimental/TechAudioTools/Source/TechAudioToolsMetaSound/Public/ViewModels/MetaSoundViewModel.h` (Public)


#### class `UMetaSoundViewModel`  
`class UMetaSoundViewModel : public UMVVMViewModelBase`  
_L23-126_
- reflection: `UCLASS(MinimalAPI, DisplayName = "MetaSound Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: The base class for MetaSound viewmodels. Used for binding metadata and member inputs/outputs of a MetaSound to widgets in UMG. Can be initialized using a MetaSound Builder or a MetaSound asset. Creates member viewmodels for each input and output in the MetaSound upon initialization.
- L30 _protected member_ `bool bIsInitialized = false;` — `UPROPERTY(BlueprintReadOnly, FieldNotify, Getter = "IsInitialized", Category = "MetaSound Viewmodel", meta = (AllowPrivateAccess))` — True if this MetaSound Viewmodel has been initialized.
- L34 _protected member_ `bool bIsPreset = false;` — `UPROPERTY(BlueprintReadOnly, FieldNotify, Getter = "IsPreset", Category = "MetaSound Viewmodel", meta = (AllowPrivateAccess))` — True if the initialized MetaSound is a preset.
- L39 _public function_ `FString GetBuilderName() const` — `UFUNCTION(BlueprintCallable, FieldNotify, Category = "MetaSound Viewmodel")` — Returns the object name of the initialized builder.
- L43 _public prototype_ `virtual TArray<UMetaSoundInputViewModel*> GetInputViewModels() const;` — `UFUNCTION(BlueprintCallable, FieldNotify, DisplayName = "Get Input Viewmodels", Category = "MetaSound Viewmodel")` — Contains MetaSound Input Viewmodels for each input of the initialized MetaSound.
- L47 _public prototype_ `UMetaSoundInputViewModel* FindInputViewModel(const FName InputViewModelName) const;` — `UFUNCTION(BlueprintCallable, DisplayName = "Find Input Viewmodel", Category = "MetaSound Viewmodel")` — Returns the input viewmodel with the given name if it exists, else returns nullptr.
- L51 _public prototype_ `virtual TArray<UMetaSoundOutputViewModel*> GetOutputViewModels() const;` — `UFUNCTION(BlueprintCallable, FieldNotify, DisplayName = "Get Output Viewmodels", Category = "MetaSound Viewmodel")` — Contains MetaSound Output Viewmodels for each output of the initialized MetaSound.
- L55 _public prototype_ `UMetaSoundOutputViewModel* FindOutputViewModel(const FName OutputViewModelName) const;` — `UFUNCTION(BlueprintCallable, DisplayName = "Find Output Viewmodel", Category = "MetaSound Viewmodel")` — Returns the output viewmodel with the given name if it exists, else returns nullptr.
- L59 _public prototype_ `virtual void InitializeMetaSound(const TScriptInterface<IMetaSoundDocumentInterface> InMetaSound);` — `UFUNCTION(BlueprintCallable, DisplayName = "Initialize MetaSound", Category = "Audio|MetaSound Viewmodel")` — Initializes the viewmodel using the given MetaSound asset.
- L63 _public prototype_ `virtual void Initialize(UMetaSoundBuilderBase* InBuilder);` — `UFUNCTION(BlueprintCallable, DisplayName = "Initialize Builder", Category = "Audio|MetaSound Viewmodel")` — Initializes the viewmodel using the given builder.
- L67 _public prototype_ `virtual void Reset();` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound Viewmodel")` — Resets this MetaSoundViewModel instance to an uninitialized state.
- L69 _public function_ `bool IsInitialized() const`
- L70 _public function_ `bool IsPreset() const`
- L72 _public prototype_ `void SetIsInitialized(const bool bInIsInitialized);`
- L74 _public prototype_ `void SetInputName(const FName& OldName, const FName& NewName) const;`
- L75 _public prototype_ `void SetInputDataType(const FName& InputName, const FName& DataType) const;`
- L76 _public prototype_ `void SetInputDefaultLiteral(const FName& InputName, const FMetasoundFrontendLiteral& DefaultLiteral) const;`
- L77 _public prototype_ `void SetInputOverridesDefault(const FName& InputName, bool bOverridesDefault) const;`
- L78 _public prototype_ `void SetInputIsConstructorPin(const FName& InputName, bool bIsConstructorPin) const;`
- L80 _public prototype_ `void SetOutputName(const FName& OldName, const FName& NewName) const;`
- L81 _public prototype_ `void SetOutputDataType(const FName& OutputName, const FName& DataType) const;`
- L82 _public prototype_ `void SetOutputIsConstructorPin(const FName& OutputName, bool bIsConstructorPin) const;`
- L85 _public prototype_ `void OnInputAdded(FName VertexName, FName DataType);` — `UFUNCTION()`
- L87 _public prototype_ `void OnInputRemoved(FName VertexName, FName DataType);` — `UFUNCTION()`
- L89 _public prototype_ `void OnInputNameChanged(FName OldName, FName NewName);` — `UFUNCTION()`
- L91 _public prototype_ `void OnInputDataTypeChanged(FName VertexName, FName DataType);` — `UFUNCTION()`
- L93 _public prototype_ `void OnInputDefaultChanged(FName VertexName, FMetasoundFrontendLiteral LiteralValue, FName PageName, EMetaSoundLiteralChangeType ChangeType = EMetaSoundLiteralChangeType::Invalid);` — `UFUNCTION()`
- L95 _public prototype_ `void OnInputInheritsDefaultChanged(FName VertexName, bool bInheritsDefault);` — `UFUNCTION()`
- L97 _public prototype_ `void OnInputIsConstructorPinChanged(FName VertexName, bool bIsConstructorPin);` — `UFUNCTION()`
- L100 _public prototype_ `void OnOutputAdded(FName VertexName, FName DataType);` — `UFUNCTION()`
- L102 _public prototype_ `void OnOutputRemoved(FName VertexName, FName DataType);` — `UFUNCTION()`
- L104 _public prototype_ `void OnOutputNameChanged(FName OldName, FName NewName);` — `UFUNCTION()`
- L106 _public prototype_ `void OnOutputDataTypeChanged(FName VertexName, FName DataType);` — `UFUNCTION()`
- L108 _public prototype_ `void OnOutputIsConstructorPinChanged(FName VertexName, bool bIsConstructorPin);` — `UFUNCTION()`
- L111 _protected prototype_ `void CreateMemberViewModels();`
- L112 _protected prototype_ `virtual UMetaSoundInputViewModel* CreateInputViewModel(const FMetasoundFrontendClassInput& InInput);`
- L113 _protected prototype_ `virtual UMetaSoundOutputViewModel* CreateOutputViewModel(const FMetasoundFrontendClassOutput& InOutput);`
- L115 _protected prototype_ `virtual TSubclassOf<UMetaSoundInputViewModel> GetInputViewModelClass() const;`
- L116 _protected prototype_ `virtual TSubclassOf<UMetaSoundOutputViewModel> GetOutputViewModelClass() const;`
- L119 _protected member_ `TObjectPtr<UMetaSoundBuilderBase> Builder;` — `UPROPERTY(Transient)`
- L122 _protected member_ `TMap<FName, TObjectPtr<UMetaSoundInputViewModel>> InputViewModels;` — `UPROPERTY(Transient)`
- L125 _protected member_ `TMap<FName, TObjectPtr<UMetaSoundOutputViewModel>> OutputViewModels;` — `UPROPERTY(Transient)`

#### class `UMetaSoundInputViewModel`  
`class UMetaSoundInputViewModel : public UMVVMViewModelBase`  
_L133-193_
- reflection: `UCLASS(MinimalAPI, DisplayName = "MetaSound Input Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel class for MetaSound inputs. Allows widgets in UMG to bind to MetaSound literals. Useful for creating knobs, sliders, and other widgets for setting MetaSound input parameters.
- L140 _protected member_ `bool bIsInitialized = false;` — `UPROPERTY(BlueprintReadOnly, FieldNotify, Getter = "IsInitialized", Category = "MetaSound Input", meta = (AllowPrivateAccess))` — True if this MetaSoundInputViewModel has been initialized.
- L144 _protected member_ `FName InputName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, FieldNotify, Getter, Setter, Category = "MetaSound Input", meta = (AllowPrivateAccess))` — The name of the initialized MetaSound input.
- L148 _protected member_ `FName DataType;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, Category = "MetaSound Input", meta = (AllowPrivateAccess))` — The data type of the initialized MetaSound input.
- L152 _protected member_ `bool bIsArray;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter = "IsArray", Setter = "SetIsArray", Category = "MetaSound Input", meta = (AllowPrivateAccess))` — True if the initialized MetaSound input is an array.
- L156 _protected member_ `bool bIsConstructorPin;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter = "IsConstructorPin", Setter = "SetIsConstructorPin", Category = "MetaSound Input", meta = (AllowPrivateAccess))` — True if the initialized MetaSound input is a constructor pin.
- L160 _protected member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, Category = "MetaSound Input", meta = (AllowPrivateAccess))` — The MetaSound Literal belonging to the initialized MetaSound input.
- L164 _protected member_ `EMetasoundFrontendLiteralType LiteralType;` — `UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Category = "MetaSound Input", meta = (AllowPrivateAccess))` — Returns the Literal Type belonging to the initialized MetaSound input.
- L168 _protected member_ `bool bOverridesDefault;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter = "OverridesDefault", Setter = "SetOverridesDefault", Category = "MetaSound Input", meta = (AllowPrivateAccess))` — True if the initialized MetaSound input overrides its value from a parent graph.
- L171 _public function_ `bool IsInitialized() const`
- L172 _public function_ `FName GetInputName() const`
- L173 _public function_ `FName GetDataType() const`
- L174 _public function_ `bool IsArray() const`
- L175 _public function_ `bool IsConstructorPin() const`
- L176 _public function_ `FMetasoundFrontendLiteral GetLiteral() const`
- L177 _public function_ `EMetasoundFrontendLiteralType GetLiteralType() const`
- L178 _public function_ `bool OverridesDefault() const`
- L180 _public prototype_ `void SetIsInitialized(const bool bInIsInitialized);`
- L181 _public prototype_ `void SetInputName(const FName& NewName);`
- L182 _public prototype_ `void SetDataType(const FName& InDataType);`
- L183 _public prototype_ `void SetIsArray(bool bInIsArray);`
- L184 _public prototype_ `void SetIsConstructorPin(bool bInIsConstructorPin);`
- L185 _public prototype_ `void SetLiteral(const FMetasoundFrontendLiteral& InLiteral);`
- L186 _public prototype_ `void SetOverridesDefault(bool bInOverridesDefaultValue);`
- L188 _public prototype_ `void OnInputNameChanged(const FName& NewName);`
- L189 _public prototype_ `void OnInputDataTypeChanged(const FName& NewDataType);`
- L190 _public prototype_ `void OnInputDefaultChanged(const FMetasoundFrontendLiteral& LiteralValue, const FName& PageName, EMetaSoundLiteralChangeType ChangeType = EMetaSoundLiteralChangeType::Invalid);`
- L191 _public prototype_ `void OnInputInheritsDefaultChanged(const bool bInheritsDefault);`
- L192 _public prototype_ `void OnInputIsConstructorPinChanged(const bool bNewIsConstructorPin);`

#### class `UMetaSoundOutputViewModel`  
`class UMetaSoundOutputViewModel : public UMVVMViewModelBase`  
_L200-241_
- reflection: `UCLASS(MinimalAPI, DisplayName = "MetaSound Output Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel class for MetaSound outputs. Allows widgets in UMG to bind to data from a MetaSound output. Useful for driving visual parameters using MetaSound outputs.
- L207 _protected member_ `bool bIsInitialized = false;` — `UPROPERTY(BlueprintReadOnly, FieldNotify, Category = "MetaSound Output", meta = (AllowPrivateAccess))` — True if this MetaSoundOutputViewModel has been initialized.
- L211 _protected member_ `FName OutputName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, FieldNotify, Setter, Category = "MetaSound Output", meta = (AllowPrivateAccess))` — The name of the initialized MetaSound output.
- L215 _protected member_ `FName DataType;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Category = "MetaSound Output", meta = (AllowPrivateAccess))` — The data type of the initialized MetaSound output.
- L219 _protected member_ `bool bIsArray;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter = "IsArray", Setter = "SetIsArray", Category = "MetaSound Output", meta = (AllowPrivateAccess))` — True if the initialized MetaSound output is an array.
- L223 _protected member_ `bool bIsConstructorPin;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter = "IsConstructorPin", Setter = "SetIsConstructorPin", Category = "MetaSound Output", meta = (AllowPrivateAccess))` — True if the initialized MetaSound output is a constructor pin.
- L226 _public function_ `bool IsInitialized() const`
- L227 _public function_ `FName GetOutputName() const`
- L228 _public function_ `FName GetDataType() const`
- L229 _public function_ `bool IsArray() const`
- L230 _public function_ `bool IsConstructorPin() const`
- L232 _public prototype_ `void SetIsInitialized(const bool bInIsInitialized);`
- L233 _public prototype_ `void SetOutputName(const FName& NewName) const;`
- L234 _public prototype_ `void SetDataType(const FName& InDataType);`
- L235 _public prototype_ `void SetIsArray(bool bInIsArray);`
- L236 _public prototype_ `void SetIsConstructorPin(bool bInIsConstructorPin);`
- L238 _public prototype_ `void OnOutputNameChanged(const FName& NewName);`
- L239 _public prototype_ `void OnOutputDataTypeChanged(const FName& NewDataType);`
- L240 _public prototype_ `void OnOutputIsConstructorPinChanged(const bool bNewIsConstructorPin);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TECHAUDIOTOOLSMETASOUND_API`

### `Plugins/Experimental/TechAudioTools/Source/TechAudioToolsMetaSound/Public/ViewModels/MetaSoundViewModelConversionFunctions.h` (Public)


#### class `UMetaSoundViewModelConversionFunctions`  
`class UMetaSoundViewModelConversionFunctions : public UBlueprintFunctionLibrary`  
_L44-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Collection of conversion functions to use with MetaSound Viewmodels.
- L51 _public prototype_ `static UMetaSoundInputViewModel* FindInputViewModelByName(const TArray<UMetaSoundInputViewModel*>& MetaSoundInputViewModels, const FName InputName);` — `UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Find MetaSound Input Viewmodel by Name", Category = "TechAudioTools")` — Searches the given array of MetaSoundInputViewModels for the specified input. Returns nullptr if unable to find a matching viewmodel.
- L55 _public prototype_ `static UMetaSoundOutputViewModel* FindOutputViewModelByName(const TArray<UMetaSoundOutputViewModel*>& MetaSoundOutputViewModels, const FName OutputName);` — `UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Find MetaSound Output Viewmodel by Name", Category = "TechAudioTools")` — Searches the given array of MetaSoundOutputViewModels for the specified output. Returns nullptr if unable to find a matching viewmodel.
- L59 _public prototype_ `static FText GetLiteralValueAsText(const FMetasoundFrontendLiteral& Literal);` — `UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get MetaSound Literal Value as Text", Category = "TechAudioTools")` — Returns the value of the given MetaSound Literal as a text value.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TechAudioTools`
- L14 _namespace_ `namespace MetaSound` (scope `TechAudioTools`)
- L17 _function_ `inline FName GetAdjustedDataType(const FName& DataType, const bool bIsArray)` (scope `TechAudioTools::MetaSound`) — Returns the given data type with the array type specifier added or removed to match bIsArray.
