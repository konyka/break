# Plugins / TechAudioToolsMetaSoundEditor

- module root: `Plugins/Experimental/TechAudioTools/Source/TechAudioToolsMetaSoundEditor`
- headers: 2; symbols: 94
- symbol kinds: class=4, function=31, macro=1, member=15, prototype=43
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: Blutility, Core, MetasoundEditor, MetasoundEngine, MetasoundFrontend, ModelViewViewModel, ModelViewViewModelEditor, TechAudioTools, TechAudioToolsMetaSound, UnrealEd

### `Plugins/Experimental/TechAudioTools/Source/TechAudioToolsMetaSoundEditor/Public/ViewModels/MetaSoundEditorViewModel.h` (Public)


#### class `UMetaSoundEditorViewModel`  
`class UMetaSoundEditorViewModel : public UMetaSoundViewModel`  
_L19-125_
- reflection: `UCLASS(MinimalAPI, DisplayName = "MetaSound Editor Viewmodel")`
- inherits: `UMetaSoundViewModel`
- desc: Editor viewmodel for MetaSounds. Creates MetaSoundEditorBuilderListener bindings upon initialization, allowing changes made to assets in the MetaSound Editor to be reflected in UMG widgets.
- L26 _protected member_ `FText DisplayName;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter = "SetMetaSoundDisplayName", Category = "MetaSound Viewmodel|Metadata", meta = (AllowPrivateAccess))` — Sets the display name of the initialized MetaSound.
- L30 _protected member_ `FText Description;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter = "SetMetaSoundDescription", Category = "MetaSound Viewmodel|Metadata", meta = (AllowPrivateAccess))` — Sets the description of the initialized MetaSound.
- L34 _protected member_ `FString Author;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, Category = "MetaSound Viewmodel|Metadata", meta = (AllowPrivateAccess))` — Sets the author of the initialized MetaSound.
- L38 _protected member_ `TArray<FText> Keywords;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, Category = "MetaSound Viewmodel|Metadata", meta = (AllowPrivateAccess))` — Sets the keywords of the initialized MetaSound.
- L42 _protected member_ `TArray<FText> CategoryHierarchy;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, Category = "MetaSound Viewmodel|Metadata", meta = (AllowPrivateAccess))` — Sets the category hierarchy of the initialized MetaSound.
- L46 _protected member_ `bool bIsDeprecated = false;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter = "IsDeprecated", Setter = "SetIsDeprecated", Category = "MetaSound Viewmodel|Metadata", meta = (AllowPrivateAccess))` — Sets the initialized MetaSound asset as deprecated.
- L49 _public function_ `virtual bool IsEditorOnly() const override`
- L51 _public prototype_ `virtual void InitializeMetaSound(const TScriptInterface<IMetaSoundDocumentInterface> InMetaSound) override;`
- L52 _public prototype_ `virtual void Initialize(UMetaSoundBuilderBase* InBuilder) override;`
- L53 _public prototype_ `virtual void Reset() override;`
- L55 _public function_ `FText GetDisplayName() const`
- L56 _public function_ `FText GetDescription() const`
- L57 _public function_ `FString GetAuthor() const`
- L58 _public function_ `TArray<FText> GetKeywords() const`
- L59 _public function_ `TArray<FText> GetCategoryHierarchy() const`
- L60 _public function_ `bool IsDeprecated() const`
- L62 _public prototype_ `void SetMetaSoundDisplayName(const FText& InDisplayName);`
- L63 _public prototype_ `void SetMetaSoundDescription(const FText& InDescription);`
- L64 _public prototype_ `void SetAuthor(const FString& InAuthor);`
- L65 _public prototype_ `void SetKeywords(const TArray<FText>& InKeywords);`
- L66 _public prototype_ `void SetCategoryHierarchy(const TArray<FText>& InCategoryHierarchy);`
- L67 _public prototype_ `void SetIsDeprecated(bool bInIsDeprecated);`
- L69 _public prototype_ `void SetInputDisplayName(const FName& InputName, const FText& InDisplayName) const;`
- L70 _public prototype_ `void SetInputDescription(const FName& InputName, const FText& InDescription) const;`
- L71 _public prototype_ `void SetInputSortOrderIndex(const FName& InputName, int32 InSortOrderIndex) const;`
- L72 _public prototype_ `void SetInputIsAdvancedDisplay(const FName& InputName, bool bInIsAdvancedDisplay) const;`
- L74 _public prototype_ `void SetOutputDisplayName(const FName& OutputName, const FText& InDisplayName) const;`
- L75 _public prototype_ `void SetOutputDescription(const FName& OutputName, const FText& InDescription) const;`
- L76 _public prototype_ `void SetOutputSortOrderIndex(const FName& OutputName, int32 InSortOrderIndex) const;`
- L77 _public prototype_ `void SetOutputIsAdvancedDisplay(const FName& OutputName, bool bInIsAdvancedDisplay) const;`
- L80 _public prototype_ `void OnGraphInputDefaultChanged(const FGraphInputDefaultChangedArgs& Args);` — `UFUNCTION()`
- L83 _public function_ `void OnDisplayNameChanged(const FText NewDisplayName)` — `UFUNCTION()`
- L85 _public function_ `void OnDescriptionChanged(const FText NewDescription)` — `UFUNCTION()`
- L87 _public function_ `void OnAuthorChanged(const FString NewAuthor)` — `UFUNCTION()`
- L89 _public function_ `void OnKeywordsChanged(const TArray<FText> NewKeywords)` — `UFUNCTION()`
- L91 _public function_ `void OnCategoryHierarchyChanged(const TArray<FText> NewCategoryHierarchy)` — `UFUNCTION()`
- L93 _public function_ `void OnIsDeprecatedChanged(const bool bNewIsDeprecated)` — `UFUNCTION()`
- L96 _public prototype_ `void OnInputDisplayNameChanged(FName InputName, FText InDisplayName);` — `UFUNCTION()`
- L98 _public prototype_ `void OnInputDescriptionChanged(FName InputName, FText InDescription);` — `UFUNCTION()`
- L100 _public prototype_ `void OnInputSortOrderIndexChanged(FName InputName, int32 InSortOrderIndex);` — `UFUNCTION()`
- L102 _public prototype_ `void OnInputIsAdvancedDisplayChanged(FName InputName, bool bInIsAdvancedDisplay);` — `UFUNCTION()`
- L105 _public prototype_ `void OnOutputDisplayNameChanged(FName OutputName, const FText InDisplayName);` — `UFUNCTION()`
- L107 _public prototype_ `void OnOutputDescriptionChanged(FName OutputName, const FText InDescription);` — `UFUNCTION()`
- L109 _public prototype_ `void OnOutputSortOrderIndexChanged(FName OutputName, int32 InSortOrderIndex);` — `UFUNCTION()`
- L111 _public prototype_ `void OnOutputIsAdvancedDisplayChanged(FName OutputName, bool bInIsAdvancedDisplay);` — `UFUNCTION()`
- L115 _protected member_ `TObjectPtr<UMetaSoundEditorBuilderListener> BuilderListener;` — `UPROPERTY(Transient)`
- L117 _protected prototype_ `virtual UMetaSoundInputViewModel* CreateInputViewModel(const FMetasoundFrontendClassInput& InInput) override;`
- L118 _protected prototype_ `virtual UMetaSoundOutputViewModel* CreateOutputViewModel(const FMetasoundFrontendClassOutput& InOutput) override;`
- L120 _protected prototype_ `virtual TSubclassOf<UMetaSoundInputViewModel> GetInputViewModelClass() const override;`
- L121 _protected prototype_ `virtual TSubclassOf<UMetaSoundOutputViewModel> GetOutputViewModelClass() const override;`
- L123 _protected prototype_ `void BindDelegates();`
- L124 _protected prototype_ `void UnbindDelegates();`

#### class `UMetaSoundInputEditorViewModel`  
`class UMetaSoundInputEditorViewModel : public UMetaSoundInputViewModel`  
_L131-169_
- reflection: `UCLASS(MinimalAPI, DisplayName = "MetaSound Input Editor Viewmodel")`
- inherits: `UMetaSoundInputViewModel`
- desc: Editor viewmodel class for MetaSound inputs. Extends the runtime MetaSoundInputViewModel with editor-only functionality.
- L138 _protected member_ `FText InputDisplayName;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Category = "MetaSound Input", meta = (AllowPrivateAccess))` — Sets the display name of the initialized MetaSound input.
- L142 _protected member_ `FText InputDescription;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Category = "MetaSound Input", meta = (AllowPrivateAccess))` — Sets the description of the initialized MetaSound input.
- L146 _protected member_ `int32 SortOrderIndex;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Category = "MetaSound Input", meta = (AllowPrivateAccess))` — Sets the sort order index of the initialized MetaSound input.
- L150 _protected member_ `bool bIsAdvancedDisplay;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = "SetIsAdvancedDisplay", Category = "MetaSound Input", meta = (AllowPrivateAccess))` — Sets whether the initialized MetaSound input should be located in the Advanced Display category.
- L153 _public function_ `virtual bool IsEditorOnly() const override`
- L155 _public function_ `FText GetInputDisplayName() const`
- L156 _public function_ `FText GetInputDescription() const`
- L157 _public function_ `int32 GetSortOrderIndex() const`
- L158 _public function_ `bool IsAdvancedDisplay() const`
- L160 _public prototype_ `void SetInputDisplayName(const FText& InDisplayName);`
- L161 _public prototype_ `void SetInputDescription(const FText& InDescription);`
- L162 _public prototype_ `void SetSortOrderIndex(int32 InSortOrderIndex);`
- L163 _public prototype_ `void SetIsAdvancedDisplay(bool bInIsAdvancedDisplay);`
- L165 _public function_ `void OnInputDisplayNameChanged(const FText& NewDisplayName)`
- L166 _public function_ `void OnInputDescriptionChanged(const FText& NewDescription)`
- L167 _public function_ `void OnInputSortOrderIndexChanged(const int32 NewSortOrderIndex)`
- L168 _public function_ `void OnInputIsAdvancedDisplayChanged(const bool bNewIsAdvancedDisplay)`

#### class `UMetaSoundOutputEditorViewModel`  
`class UMetaSoundOutputEditorViewModel : public UMetaSoundOutputViewModel`  
_L175-213_
- reflection: `UCLASS(MinimalAPI, DisplayName = "MetaSound Output Editor Viewmodel")`
- inherits: `UMetaSoundOutputViewModel`
- desc: Editor viewmodel class for MetaSound outputs. Extends the runtime MetaSoundOutputViewModel with editor-only functionality.
- L182 _protected member_ `FText OutputDisplayName;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Category = "MetaSound Output", meta = (AllowPrivateAccess))` — Sets the display name of the initialized MetaSound output.
- L186 _protected member_ `FText OutputDescription;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Category = "MetaSound Output", meta = (AllowPrivateAccess))` — Sets the description of the initialized MetaSound output.
- L190 _protected member_ `int32 SortOrderIndex;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Category = "MetaSound Output", meta = (AllowPrivateAccess))` — Sets the sort order index of the initialized MetaSound output.
- L194 _protected member_ `bool bIsAdvancedDisplay;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = "SetIsAdvancedDisplay", Category = "MetaSound Output", meta = (AllowPrivateAccess))` — Sets whether the initialized MetaSound output should be located in the Advanced Display category.
- L197 _public function_ `virtual bool IsEditorOnly() const override`
- L199 _public function_ `FText GetOutputDisplayName() const`
- L200 _public function_ `FText GetOutputDescription() const`
- L201 _public function_ `int32 GetSortOrderIndex() const`
- L202 _public function_ `bool IsAdvancedDisplay() const`
- L204 _public prototype_ `void SetOutputDisplayName(const FText& InDisplayName);`
- L205 _public prototype_ `void SetOutputDescription(const FText& InDescription);`
- L206 _public prototype_ `void SetSortOrderIndex(int32 InSortOrderIndex);`
- L207 _public prototype_ `void SetIsAdvancedDisplay(bool bInIsAdvancedDisplay);`
- L209 _public function_ `void OnOutputDisplayNameChanged(const FText& NewDisplayName)`
- L210 _public function_ `void OnOutputDescriptionChanged(const FText& NewDescription)`
- L211 _public function_ `void OnOutputSortOrderIndexChanged(const int32 NewSortOrderIndex)`
- L212 _public function_ `void OnOutputIsAdvancedDisplayChanged(const bool NewIsAdvancedDisplay)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TECHAUDIOTOOLSMETASOUNDEDITOR_API`

### `Plugins/Experimental/TechAudioTools/Source/TechAudioToolsMetaSoundEditor/Public/ViewModels/MetaSoundEditorViewModelConversionFunctions.h` (Public)


#### class `UMetaSoundEditorViewModelConversionFunctions`  
`class UMetaSoundEditorViewModelConversionFunctions : public UBlueprintFunctionLibrary`  
_L13-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Collection of conversion functions to use with MetaSound Editor Viewmodels.
- L18 _public prototype_ `virtual bool IsEditorOnly() const override;`
- L19 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L23 _public prototype_ `static FLinearColor GetMetaSoundDataTypePinColor(const FName& DataType);` — `UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get MetaSound Data Type Pin Color", Category = "TechAudioTools")` — Returns the pin color associated with the given data type.
