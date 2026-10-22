# Plugins / ModelViewViewModel

- module root: `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel`
- headers: 41; symbols: 1081
- symbol kinds: class=27, delegate=8, enum=13, enumerator=71, function=259, macro=20, member=244, namespace=61, prototype=296, struct=68, typedef=13, union=1
- PrivateDependencyModuleNames: Slate, SlateCore, UMG, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, FieldNotification

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Private/ModelViewViewModelModule.h` (Private)


#### class `FModelViewViewModelModule`  
`class FModelViewViewModelModule : public IModelViewViewModelModule`  
_L18-53_
- inherits: `IModelViewViewModelModule`
- L21 _public prototype_ `FModelViewViewModelModule() = default;`
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnBlueprintCompiled) FOnBlueprintCompiled OnBlueprintCompiled;`
- L32 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnBlueprintPreCompile, UBlueprint*) FOnBlueprintPreCompile OnBlueprintPreCompile;`
- L36 _public prototype_ `virtual void RegisterImplicitConverter(const TSharedRef<FMVVMImplicitConverter>& Converter) override;`
- L37 _public prototype_ `virtual void UnregisterImplicitConverter(const TSharedRef<FMVVMImplicitConverter>& Converter) override;`
- L38 _public function_ `TConstArrayView<TSharedPtr<FMVVMImplicitConverter>> GetImplicitConverters() const`
- L41 _private prototype_ `void HandleDefaultExecutionModeChanged(IConsoleVariable* Variable);`
- L42 _private prototype_ `void OnPostEngineInit();`
- L44 _private prototype_ `void HandleBlueprintCompiled();`
- L45 _private prototype_ `void HandleBlueprintPreCompile(UBlueprint* Blueprint);`
- L47 _private member_ `FDelegateHandle OnBlueprintCompiledHandle;`
- L48 _private member_ `FDelegateHandle OnBlueprintPreCompileHandle;`
- L51 _private member_ `TArray<TSharedPtr<FMVVMImplicitConverter>> ImplicitConverters;`
- L52 _private member_ `TSharedPtr<FMVVMNumericImplicitConverter> NumericConverter;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_STATS_GROUP(TEXT("UMG Viewmodel"), STATGROUP_UMG_Viewmodel, STATC`
- L29 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnBlueprintCompiled) FOnBlueprintCompiled OnBlueprintCompiled;`
- L32 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnBlueprintPreCompile, UBlueprint*) FOnBlueprintPreCompile OnBlueprintPreCompile;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Private/View/MVVMBindingSubsystem.h` (Private)


#### class `UMVVMBindingSubsystem`  
`class UMVVMBindingSubsystem : public UEngineSubsystem, public FTickableGameObject`  
_L16-50_
- reflection: `UCLASS(NotBlueprintable, Hidden)`
- inherits: `UEngineSubsystem,FTickableGameObject`
- L21 _public prototype_ `void AddViewWithTickBinding(const UMVVMView* View);`
- L22 _public prototype_ `void RemoveViewWithTickBinding(const UMVVMView* View);`
- L24 _public prototype_ `void AddDelayedBinding(const UMVVMView* View, FMVVMViewClass_BindingKey BindingKey);`
- L25 _public prototype_ `void RemoveDelayedBindings(const UMVVMView* View);`
- L26 _public prototype_ `void RemoveDelayedBindings(const UMVVMView* View, FMVVMViewClass_SourceKey SourceKey);`
- L29 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L33 _public function_ `virtual bool IsTickableInEditor() const override`
- L37 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L42 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L43 _public prototype_ `virtual TStatId GetStatId() const override;`
- L46 _private typedef_ `using FDelayedBindingList = TArray<FMVVMViewClass_BindingKey, TInlineAllocator<8>>;`
- L47 _private typedef_ `using FDelayedBindingMap = TMap<TObjectKey<const UMVVMView>, FDelayedBindingList>;`
- L48 _private member_ `FDelayedBindingMap DelayedBindings;`
- L49 _private member_ `TArray<TWeakObjectPtr<const UMVVMView>> ViewsWithTickBindings;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Bindings/ConversionLibraries/MVVMFontConversionLibrary.h` (Public)


#### class `UMVVMFontConversionLibrary`  
`class UMVVMFontConversionLibrary : public UBlueprintFunctionLibrary`  
_L24-120_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Conversion library that contains methods for FSlateFontInfo Primarily consists of methods to set material params on an existing FSlateFontInfo
- L38 _public prototype_ `static FSlateFontInfo Conv_SetScalarParameter(FSlateFontInfo Font, FName ParameterName, float Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Scalar Parameter (Font)", MVVMBindToDestination = "Font"))` — Sets a scalar value on a font material assuming it exists, handles MID existance appropriately @param Font			Font with a material we want to set a parameter on @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L48 _public prototype_ `static FSlateFontInfo Conv_SetVectorParameter(FSlateFontInfo Font, FName ParameterName, FLinearColor Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Vector Parameter (Font)", MVVMBindToDestination = "Font"))` — Sets a vector value on a font material assuming it exists, handles MID existance appropriately @param Font			Font with a material we want to set a parameter on @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L58 _public prototype_ `static FSlateFontInfo Conv_SetVectorParameter_FColor(FSlateFontInfo Font, FName ParameterName, FColor Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Vector Parameter (Font) from Color", MVVMBindToDestination = "Font"))` — Sets a vector value on a font material assuming it exists, handles MID existance appropriately @param Font			Font with a material we want to set a parameter on @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L68 _public prototype_ `static FSlateFontInfo Conv_SetTextureParameter(FSlateFontInfo Font, FName ParameterName, UTexture* Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Texture Parameter (Font)", MVVMBindToDestination = "Font"))` — Sets a texture value on a font material assuming it exists, handles MID existance appropriately @param Font			Font with a material we want to set a parameter on @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L79 _public prototype_ `static FSlateFontInfo Conv_SetScalarParameterMID(FSlateFontInfo Font, UMaterialInterface* Material, FName ParameterName, float Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Scalar Parameter MID (Font)", MVVMBindToDestination = "Font"))` — Sets a scalar value on a font material assuming it exists, handles MID existance appropriately @param Font			Font with a material we want to set a parameter on @param Material		Material to set on the font @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L90 _public prototype_ `static FSlateFontInfo Conv_SetVectorParameterMID(FSlateFontInfo Font, UMaterialInterface* Material, FName ParameterName, FLinearColor Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Vector Parameter MID (Font)", MVVMBindToDestination = "Font"))` — Sets a vector value on a font material assuming it exists, handles MID existance appropriately @param Font			Font with a material we want to set a parameter on @param Material		Material to set on the font @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L101 _public prototype_ `static FSlateFontInfo Conv_SetVectorParameterMID_FColor(FSlateFontInfo Font, UMaterialInterface* Material, FName ParameterName, FColor Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Vector Parameter MID (Font) from Color", MVVMBindToDestination = "Font"))` — Sets a vector value on a font material assuming it exists, handles MID existance appropriately @param Font			Font with a material we want to set a parameter on @param Material		Material to set on the font @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L112 _public prototype_ `static FSlateFontInfo Conv_SetTextureParameterMID(FSlateFontInfo Font, UMaterialInterface* Material, FName ParameterName, UTexture* Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Texture Parameter MID (Font)", MVVMBindToDestination = "Font"))` — Sets a texture value on a font material assuming it exists, handles MID existance appropriately @param Font			Font with a material we want to set a parameter on @param Material		Material to set on the font @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L119 _private prototype_ `static UMaterialInstanceDynamic* TryGetDynamicMaterial(FSlateFontInfo& InFont, UObject* InOuter, UMaterialInterface* InMaterial = nullptr);` — Tries to get a Material Instance Dynamic from the font, will create one if possible using the provided outer, else returns nullptr

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Bindings/ConversionLibraries/MVVMSlateBrushConversionLibrary.h` (Public)


#### class `UMVVMSlateBrushConversionLibrary`  
`class UMVVMSlateBrushConversionLibrary : public UBlueprintFunctionLibrary`  
_L24-122_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Conversion library that contains methods for FSlateBrush Primarily consists of methods to set material params on an existing FSlateBrush
- L38 _public prototype_ `static FSlateBrush Conv_SetScalarParameter(FSlateBrush Brush, FName ParameterName, float Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Scalar Parameter (Brush)", MVVMBindToDestination = "Brush"))` — Sets a scalar value on a brush material assuming it exists, handles MID existance appropriately @param Brush			Brush with a material we want to set a parameter on @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L48 _public prototype_ `static FSlateBrush Conv_SetVectorParameter(FSlateBrush Brush, FName ParameterName, FLinearColor Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Vector Parameter (Brush)", MVVMBindToDestination = "Brush"))` — Sets a vector value on a brush material assuming it exists, handles MID existance appropriately @param Brush			Brush with a material we want to set a parameter on @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L58 _public prototype_ `static FSlateBrush Conv_SetVectorParameter_FColor(FSlateBrush Brush, FName ParameterName, FColor Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Vector Parameter (Brush) from Color", MVVMBindToDestination = "Brush"))` — Sets a vector value on a brush material assuming it exists, handles MID existance appropriately @param Brush			Brush with a material we want to set a parameter on @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L69 _public prototype_ `static FSlateBrush Conv_SetTextureParameter(FSlateBrush Brush, FName ParameterName, UTexture* Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Texture Parameter (Brush)", MVVMBindToDestination = "Brush"))` — Sets a texture value on a brush material assuming it exists, handles MID existance appropriately @param Brush			Brush with a material we want to set a parameter on @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L80 _public prototype_ `static FSlateBrush Conv_SetScalarParameterMID(FSlateBrush Brush, UMaterialInterface* Material, FName ParameterName, float Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Scalar Parameter MID (Brush)", MVVMBindToDestination = "Brush"))` — Sets a scalar value on a brush material assuming it exists, handles MID existance appropriately @param Brush			Brush with a material we want to set a parameter on @param Material		Material to set on the brush @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L91 _public prototype_ `static FSlateBrush Conv_SetVectorParameterMID(FSlateBrush Brush, UMaterialInterface* Material, FName ParameterName, FLinearColor Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Vector Parameter MID (Brush)", MVVMBindToDestination = "Brush"))` — Sets a vector value on a brush material assuming it exists, handles MID existance appropriately @param Brush			Brush with a material we want to set a parameter on @param Material		Material to set on the brush @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L102 _public prototype_ `static FSlateBrush Conv_SetVectorParameterMID_FColor(FSlateBrush Brush, UMaterialInterface* Material, FName ParameterName, FColor Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Vector Parameter MID (Brush) from Color", MVVMBindToDestination = "Brush"))` — Sets a vector value on a brush material assuming it exists, handles MID existance appropriately @param Brush			Brush with a material we want to set a parameter on @param Material		Material to set on the brush @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L114 _public prototype_ `static FSlateBrush Conv_SetTextureParameterMID(FSlateBrush Brush, UMaterialInterface* Material, FName ParameterName, UTexture* Value);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "Set Texture Parameter MID (Brush)", MVVMBindToDestination = "Brush"))` — Sets a texture value on a brush material assuming it exists, handles MID existance appropriately @param Brush			Brush with a material we want to set a parameter on @param Material		Material to set on the brush @param ParameterName	Name of material parameter to set @param Value			Value to set material parameter to
- L121 _private prototype_ `static UMaterialInstanceDynamic* TryGetDynamicMaterial(FSlateBrush& InBrush, UObject* InOuter, UMaterialInterface* InMaterial = nullptr);` — Tries to get a Material Instance Dynamic from the brush, will create one if possible using the provided outer, else returns nullptr

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Bindings/ImplicitConverters/MVVMImplicitConverter.h` (Public)


#### class `FMVVMImplicitConverter`  
`class FMVVMImplicitConverter`  
_L10-18_
- desc: Base class to support converting between simple types in MVVM bindings without the need for a conversion function
- L13 _public prototype_ `FMVVMImplicitConverter() = default;`
- L14 _public prototype_ `virtual ~FMVVMImplicitConverter() = default;`
- L16 _public prototype_ `virtual bool CanConvertImplicitly(const FProperty* Source, const FProperty* Destination) = 0;`
- L17 _public prototype_ `virtual void ConvertImplicitly(const FProperty* Source, const FProperty* Destination, void* Data) = 0;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Bindings/ImplicitConverters/MVVMNumericImplicitConverter.h` (Public)


#### class `FMVVMNumericImplicitConverter`  
`class FMVVMNumericImplicitConverter : public FMVVMImplicitConverter`  
_L10-15_
- inherits: `FMVVMImplicitConverter`
- desc: For converting between numeric types
- L13 _public prototype_ `virtual bool CanConvertImplicitly(const FProperty* Source, const FProperty* Destination) override;`
- L14 _public prototype_ `virtual void ConvertImplicitly(const FProperty* Source, const FProperty* Destination, void* Data) override;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Bindings/MVVMBindingHelper.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MVVM` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MVVM` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MVVM` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MVVM` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MVVM` (scope `UE`)
- L19 _namespace_ `namespace BindingHelper` (scope `UE::MVVM`)
- L23 _prototype_ `[[nodiscard]] bool IsValidForSourceBinding(const FProperty* InProperty);` (scope `UE::MVVM::BindingHelper`) — Is the Property usable as a source (readable) by the binding system. It may required a Getter to read it.
- L29 _prototype_ `[[nodiscard]] bool IsValidForSourceBinding(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Is the Function usable as a source (readable) by the binding system. @note It may be a BlueprintGetter and binding to the Property would be better in the editor.
- L35 _prototype_ `[[nodiscard]] bool IsValidForSourceBinding(const FMVVMConstFieldVariant InField);` (scope `UE::MVVM::BindingHelper`) — Is the Field usable as a source (readable) by the binding system. @note It may be a BlueprintGetter and binding to the Property would be better in the editor.
- L38 _prototype_ `[[nodiscard]] bool IsValidForDestinationBinding(const FProperty* InProperty);` (scope `UE::MVVM::BindingHelper`) — Is the Property usable as a destination (settable) by the binding system. It may required a Setter to write it.
- L44 _prototype_ `[[nodiscard]] bool IsValidForDestinationBinding(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Is the Function usable as a destination (settable) by the binding system. @note It may be a BlueprintSetter and binding to the Property would be better in the editor.
- L50 _prototype_ `[[nodiscard]] bool IsValidForDestinationBinding(const FMVVMConstFieldVariant InVariant);` (scope `UE::MVVM::BindingHelper`) — Is the Field usable as a destination (settable) by the binding system. @note It may be a BlueprintSetter and binding to the Property would be better in the editor.
- L56 _prototype_ `[[nodiscard]] bool IsValidForSimpleRuntimeConversion(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Is the Function usable as a conversion function by the binding system without any wrapper. A simple conversion takes a single argument and returns a single value.
- L62 _prototype_ `[[nodiscard]] bool IsValidForComplexRuntimeConversion(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Is the Function usable as a conversion function by the binding system with a wrapper. A complex conversion takes a no argument and returns a single value.
- L68 _prototype_ `[[nodiscard]] bool IsValidForDelegateSignatureBinding(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Is the Function usable as a delegate signature binding. Delegate signature functions are used for binding to generated events
- L74 _prototype_ `[[nodiscard]] bool IsValidForEventBinding(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Is the Function usable as an event binding. Events can trigger functions with any number of parameters and any return values.
- L79 _prototype_ `[[nodiscard]] bool IsValidForEventBinding(const FMVVMConstFieldVariant InVariant);` (scope `UE::MVVM::BindingHelper`) — Is the Field usable as an event binding by the binding system.
- L83 _prototype_ `[[nodiscard]] bool IsAccessibleDirectlyForSourceBinding(const FProperty* InProperty);` (scope `UE::MVVM::BindingHelper`) — Is the Property usable as a source by the binding system and can it be read directly or it requires a Getter.
- L86 _prototype_ `[[nodiscard]] bool IsAccessibleDirectlyForDestinationBinding(const FProperty* InProperty);` (scope `UE::MVVM::BindingHelper`) — Is the Property usable as a destination by the binding system and can it be write directly or it requires a Setter.
- L89 _prototype_ `[[nodiscard]] bool IsAccessibleWithGetterForSourceBinding(const FProperty* InProperty);` (scope `UE::MVVM::BindingHelper`) — Is the Property usable as a source by the binding system and a Getter exists.
- L92 _prototype_ `[[nodiscard]] bool IsAccessibleWithSetterForDestinationBinding(const FProperty* InProperty);` (scope `UE::MVVM::BindingHelper`) — Is the Property usable as a destination by the binding system and a Setter exists.
- L98 _prototype_ `[[nodiscard]] FName GetDelegateSignatureName(FName InGraphName);` (scope `UE::MVVM::BindingHelper`) — Converts a given graph / function name into it's delegate signature name (By appending the correct UE suffix).
- L104 _prototype_ `[[nodiscard]] FMVVMFieldVariant FindFieldByName(const UStruct* Container, FMVVMBindingName BindingName);` (scope `UE::MVVM::BindingHelper`) — Returns the Property or the Function that matches that BindingName. @note It doesn't check for BlueprintGetter or BlueprintSetter.
- L106 _prototype_ `[[nodiscard]] TValueOrError<const FProperty*, FText> TryGetPropertyTypeForSourceBinding(const FMVVMConstFieldVariant& InField);` (scope `UE::MVVM::BindingHelper`)
- L107 _prototype_ `[[nodiscard]] TValueOrError<const FProperty*, FText> TryGetPropertyTypeForDestinationBinding(const FMVVMConstFieldVariant& InField);` (scope `UE::MVVM::BindingHelper`)
- L108 _prototype_ `[[nodiscard]] TValueOrError<const FProperty*, FText> TryGetPropertyTypeForSourceBinding(const FProperty* InProperty);` (scope `UE::MVVM::BindingHelper`)
- L109 _prototype_ `[[nodiscard]] TValueOrError<const FProperty*, FText> TryGetPropertyTypeForDestinationBinding(const FProperty* InProperty);` (scope `UE::MVVM::BindingHelper`)
- L110 _prototype_ `[[nodiscard]] TValueOrError<const FProperty*, FText> TryGetPropertyTypeForSourceBinding(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`)
- L111 _prototype_ `[[nodiscard]] TValueOrError<const FProperty*, FText> TryGetPropertyTypeForDestinationBinding(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`)
- L114 _prototype_ `[[nodiscard]] TValueOrError<const FProperty*, FText> TryGetReturnTypeForConversionFunction(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Returns the return property for a conversion function, or an error if the function is not valid as a conversion function.
- L117 _prototype_ `[[nodiscard]] TValueOrError<TArray<const FProperty*>, FText> TryGetArgumentsForConversionFunction(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Returns the argument properties for a conversion function, or an error if the function is not valid as a conversion function.
- L120 _prototype_ `[[nodiscard]] bool ArePropertiesCompatible(const FProperty* Source, const FProperty* Destination);` (scope `UE::MVVM::BindingHelper`) — Are type the same or could be converted at runtime.
- L129 _prototype_ `[[nodiscard]] const FProperty* GetReturnProperty(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Returns the "return" property of the function. It can be a none-const ref/out argument. int Foo(double) -> returns int void Foo(int&, double) -> returns int void Foo(const int&, double) -> returns null int Foo(int&, double) -> returns null
- L137 _prototype_ `[[nodiscard]] const FProperty* GetFirstArgumentProperty(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Returns the first argument property. Ref/Out argument have to be const. int Foo(double) -> returns double void Foo(int& Out, double) -> returns double void Foo(const int& Out, double) -> returns int
- L143 _prototype_ `[[nodiscard]] TArray<const FProperty*> GetAllArgumentProperties(const UFunction* InFunction);` (scope `UE::MVVM::BindingHelper`) — Returns all argument properties of this function.
- L148 _prototype_ `[[nodiscard]] bool IsValidArgumentProperty(const FProperty* Property);` (scope `UE::MVVM::BindingHelper`) — Returns true if the given property is a valid function argument property.
- L162 _prototype_ `void ExecuteBinding_NoCheck(const FFieldContext& Source, const FFieldContext& Destination);` (scope `UE::MVVM::BindingHelper`) — Execute a binding that can be LocalValue = Src.Property; Dst.Property = LocalValue; LocalValue = Src.Property; Dst.SetProperty(LocalValue); LocalValue = Src.GetProperty(); Dst.Property = LocalValue; LocalValue = Src.GetProperty(); Dst.SetProperty(LocalValue); with conversion from float to double or integral to integral between the getter and the setter. @note No test is performed to see if the Src Property can be safely assign to the Destination Property. Use with caution. @note No test is performed to see if the Src.GetProperty can be safely executed. Use with caution. @note No test is performed to see if the Dst.SetProperty can be safely executed. Use with caution.
- L173 _prototype_ `void ExecuteBinding_NoCheck(const FFieldContext& Destination, const FFunctionContext& ConversionFunction);` (scope `UE::MVVM::BindingHelper`) — Execute a binding that can be LocalValue = ConcFuncOwner.ConversionFunction(LocalValue); Dst.Property = LocalValue; LocalValue = ConcFuncOwner.ConversionFunction(LocalValue); Dst.SetProperty(LocalValue); with conversion from float to double or integral to integral between the getter and the conversion function and/or the conversion function and the setter. @note No test is performed to see if the Dst.SetProperty can be safely executed. Use with caution. @note No test is performed to see if the ConversionFunction can be safely executed. Use with caution.
- L188 _prototype_ `void ExecuteBinding_NoCheck(const FFieldContext& Source, const FFieldContext& Destination, const FFunctionContext& ConversionFunction);` (scope `UE::MVVM::BindingHelper`) — Execute a binding that can be LocalValue = Src.Property; LocalValue = ConcFuncOwner.ConversionFunction(LocalValue); Dst.Property = LocalValue; LocalValue = Src.Property; LocalValue = ConcFuncOwner.ConversionFunction(LocalValue); Dst.SetProperty(LocalValue); LocalValue = Src.GetProperty(); LocalValue = ConcFuncOwner.ConversionFunction(LocalValue); Dst.Property = LocalValue; LocalValue = Src.GetProperty(); LocalValue = ConcFuncOwner.ConversionFunction(LocalValue); Dst.SetProperty(LocalValue); with conversion from float to double between the getter and the conversion function and/or the conversion function and the setter. @note No test is performed to see if the Src Property can be safely assign to the Destination Property. Use with caution. @note No test is performed to see if the Src.GetProperty can be safely executed. Use with caution. @note No test is performed to see if the Dst.SetProperty can be safely executed. Use with caution. @note No test is performed to see if the ConversionFunction can be safely executed. Use with caution.
- L195 _prototype_ `void ExecuteFunction_NoReturnValue(UFunction* InFunction, UObject* UserWidget);` (scope `UE::MVVM::BindingHelper`) — Execute a function with no parameters and no return value @note No test is performed to verify the function doesn't have parameters and return value. Use with caution.

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Bindings/MVVMCompiledBindingLibrary.h` (Public)


#### struct `FMVVMVCompiledFields`  
`struct FMVVMVCompiledFields`  
_L26-79_
- reflection: `USTRUCT()`
- desc: The info to fetch a list of FProperty or UFunction from a Class that will be needed by bindings.
- L32 _public function_ `int32 GetPropertyNum() const`
- L37 _public function_ `int32 GetFunctionNum() const`
- L42 _public function_ `FName GetPropertyName(const TArrayView<const FName> Names, int32 Index) const`
- L49 _public function_ `FName GetFunctionName(const TArrayView<const FName> Names, int32 Index) const`
- L56 _public function_ `const UStruct* GetStruct() const`
- L62 _public prototype_ `FProperty* GetProperty(FName PropertyName) const;` — Find the FProperty from the  Class.
- L65 _public prototype_ `UFunction* GetFunction(FName FunctionName) const;` — Find the UFunction from the Class.
- L69 _private member_ `TObjectPtr<const UStruct> ClassOrScriptStruct = nullptr;` — `UPROPERTY()`
- L72 _private member_ `int16 LibraryStartIndex = 0;` — `UPROPERTY()`
- L75 _private member_ `int16 NumberOfProperties = 0;` — `UPROPERTY()`
- L78 _private member_ `int16 NumberOfFunctions = 0;` — `UPROPERTY()`

#### struct `FMVVMVCompiledFieldPath`  
`struct FMVVMVCompiledFieldPath`  
_L84-114_
- reflection: `USTRUCT()`
- desc: Contains the info to evaluate a path for a specific library.
- L91 _public function_ `bool IsValid() const`
- L96 _public function_ `int16 GetStartIndex() const`
- L102 _private typedef_ `using IndexType = int16;`
- L105 _private member_ `int16 StartIndex = INDEX_NONE;` — `UPROPERTY()`
- L108 _private member_ `int16 Num = INDEX_NONE;` — `UPROPERTY()`
- L112 _private member_ `FGuid CompiledBindingLibraryId;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FMVVMCompiledLoadedPropertyOrFunctionIndex`  
`struct FMVVMCompiledLoadedPropertyOrFunctionIndex`  
_L119-149_
- reflection: `USTRUCT()`
- L126 _public function_ `FMVVMCompiledLoadedPropertyOrFunctionIndex()`
- L136 _private member_ `int16 Index = INDEX_NONE;` — `UPROPERTY()` — Is the index in LoadedProperties or LoadedFunctions.
- L140 _private member_ `uint8 bIsObjectProperty : 1;` — `UPROPERTY()` — Is the property or the return property of the UFunction is a FObjectPropertyBase
- L144 _private member_ `uint8 bIsScriptStructProperty : 1;` — `UPROPERTY()` — Is the property or the return property of the UFunction is a FStructProperty
- L148 _private member_ `uint8 bIsProperty : 1;` — `UPROPERTY()` — Is the index in LoadedProperties or LoadedFunctions.

#### struct `FMVVMVCompiledBinding`  
`struct FMVVMVCompiledBinding`  
_L154-252_
- reflection: `USTRUCT()`
- desc: Contains a single combination to execute a binding for a specific library.
- L162 _public function_ `bool IsValid() const`
- L170 _public function_ `FMVVMVCompiledFieldPath GetSourceFieldPath() const`
- L175 _public function_ `FMVVMVCompiledFieldPath GetDestinationFieldPath() const`
- L180 _public function_ `FMVVMVCompiledFieldPath GetConversionFunctionFieldPath() const`
- L190 _public function_ `bool HasSimpleConversionFunction() const` — A conversion function is needed to run the binding. The binding runs in native. It is on the form: Destination = ConversionFunction(Source)
- L202 _public function_ `bool HasComplexConversionFunction() const` — A conversion function is needed to run the binding. The conversion function takes more than one input. The binding doesn't requires the SourceFieldPath to execute. The binding runs in native. It is on the form Destination = ComplexConversionFunction()
- L211 _public function_ `bool IsRuntimeBinding() const` — The binding runs in native. It is on the form: Destination = Source or Destination = ConversionFunction(Source) or Destination = ComplexConversionFunction()
- L220 _public function_ `bool IsComplexBinding() const` — The binding runs with the BP virtual machine. It is on the form: Destination()
- L226 _private typedef_ `using IndexType = int16;`
- L229 _private member_ `FMVVMVCompiledFieldPath SourceFieldPath;` — `UPROPERTY()`
- L232 _private member_ `FMVVMVCompiledFieldPath DestinationFieldPath;` — `UPROPERTY()`
- L235 _private member_ `FMVVMVCompiledFieldPath ConversionFunctionFieldPath;` — `UPROPERTY()`
- L246 _private member_ `uint8 Type = (uint8)EType::None;` — `UPROPERTY()`
- L250 _private member_ `FGuid CompiledBindingLibraryId;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### enum `FMVVMVCompiledBinding::EType`  
`enum class EType : uint8`  
_L237-243_
- L239 _public enumerator_ `None = 0`
- L240 _public enumerator_ `HasConversionFunction = 1`
- L241 _public enumerator_ `HasComplexConversionFunction = 2`
- L242 _public enumerator_ `BindingComplex = 3`

#### struct `FMVVMCompiledBindingLibrary`  
`struct FMVVMCompiledBindingLibrary`  
_L257-358_
- reflection: `USTRUCT()`
- desc: Library of all the compiled bindings.
- L264 _public prototype_ `FMVVMCompiledBindingLibrary();`
- L266 _public prototype_ `FMVVMCompiledBindingLibrary(FGuid LibraryId);`
- L280 _public prototype_ `static FText LexToText(EExecutionFailingReason Reason);`
- L292 _public prototype_ `void Load();` — Fetch the FProperty and UFunction.
- L294 _public prototype_ `void Unload();` — Release the acquired FProperty and UFunction.
- L296 _public prototype_ `bool IsLoaded() const;` — FProperty and UFunction are fetched.
- L304 _public prototype_ `TValueOrError<void, EExecutionFailingReason> Execute(UObject* ExecutionSource, const FMVVMVCompiledBinding& Binding, EConversionFunctionType ConversionType) const;` — Execute a binding, in one direction. The ExecutionSource is the View (UserWidget) instance. The Source of the binding (ViewModel, UserWidget, Widget, ...) can be provided if already known. The Destination or the binding (ViewModel, UserWidget, Widget, ...) can be provided if already known.
- L305 _public prototype_ `TValueOrError<void, EExecutionFailingReason> ExecuteWithSource(UObject* ExecutionSource, const FMVVMVCompiledBinding& Binding, UObject* Source) const;`
- L312 _public prototype_ `TValueOrError<UE::MVVM::FFieldContext, void> EvaluateFieldPath(UObject* ExecutionSource, const FMVVMVCompiledFieldPath& FieldPath) const;` — Evaluate the path to find the container use by a binding. ExecutionSource is the View (UserWidget) instance. @returns the container and the last segment of the path. The last segment can be a property or a function.
- L315 _public prototype_ `TValueOrError<FString, FString> FieldPathToString(FMVVMVCompiledFieldPath FieldPath, bool bUseDisplayName) const;` — Return a readable version of the FieldPath.
- L318 _private prototype_ `TValueOrError<void, EExecutionFailingReason> ExecuteImpl(UObject* ExecutionSource, const FMVVMVCompiledBinding& Binding, UObject* Source, EConversionFunctionType ConversionType) const;`
- L319 _private prototype_ `TValueOrError<void, EExecutionFailingReason> ExecuteImpl(UE::MVVM::FFieldContext& Source, UE::MVVM::FFieldContext& Destination, UE::MVVM::FFunctionContext& ConversionFunction, EConversionFunctionType ConversionType) const;`
- L321 _private prototype_ `TValueOrError<UE::MVVM::FMVVMFieldVariant, void> GetFinalFieldFromPathImpl(UE::MVVM::FObjectVariant CurrentContainer, const FMVVMVCompiledFieldPath& FieldPath) const;`
- L323 _private prototype_ `bool CanAccessLoadedProperiesAtIndex(int16 index) const;`
- L339 _private member_ `TArray<FProperty*> LoadedProperties;`
- L340 _private member_ `TArray<FLoadedFunction> LoadedFunctions;`
- L343 _private member_ `TArray<FMVVMCompiledLoadedPropertyOrFunctionIndex> FieldPaths;` — `UPROPERTY()`
- L348 _private member_ `FGuid CompiledBindingLibraryId;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`
- L353 _private member_ `TArray<FMVVMVCompiledFields> CompiledFields;` — `UPROPERTY()` — Only needed for loading the FProperty/UFunction.
- L357 _private member_ `TArray<FName> CompiledFieldNames;` — `UPROPERTY()` — Only needed for loading the FProperty/UFunction.

#### enum `FMVVMCompiledBindingLibrary::EExecutionFailingReason`  
`enum class EExecutionFailingReason`  
_L271-278_
- L273 _public enumerator_ `IncompatibleLibrary`
- L274 _public enumerator_ `InvalidSource`
- L275 _public enumerator_ `InvalidDestination`
- L276 _public enumerator_ `InvalidConversionFunction`
- L277 _public enumerator_ `InvalidCast`

#### enum `FMVVMCompiledBindingLibrary::EConversionFunctionType`  
`enum class EConversionFunctionType`  
_L283-289_
- L286 _public enumerator_ `Simple` — accept an single argument and returns a single property
- L288 _public enumerator_ `Complex` — returns a single property. The argument are fetch from inside the function

#### struct `FMVVMCompiledBindingLibrary::FLoadedFunction`  
`struct FLoadedFunction`  
_L326-337_
- L328 _public prototype_ `FLoadedFunction() = default;`
- L329 _public prototype_ `FLoadedFunction(const UFunction* Function);`
- L331 _public member_ `TWeakObjectPtr<const UClass> ClassOwner;`
- L332 _public member_ `FName FunctionName;`
- L333 _public member_ `bool bIsFunctionVirtual = false;`
- L335 _public prototype_ `UFunction* GetFunction() const;`
- L336 _public prototype_ `UFunction* GetFunction(const UObject* CallingContext) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FieldNotification` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MVVM` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MVVM` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MVVM` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Bindings/MVVMConversionLibrary.h` (Public)


#### class `UMVVMConversionLibrary`  
`class UMVVMConversionLibrary : public UBlueprintFunctionLibrary`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L19 _private prototype_ `static ESlateVisibility Conv_BoolToSlateVisibility(bool bIsVisible, ESlateVisibility TrueVisibility = ESlateVisibility::Visible, ESlateVisibility FalseVisibility = ESlateVisibility::Collapsed);` — `UFUNCTION(BlueprintPure, Category = "Widget", meta = (DisplayName = "To Visibility (Boolean)"))` — Converts a bool to a slate visibility.

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Bindings/MVVMFieldPathHelper.h` (Public)


#### struct `UE::MVVM::FieldPathHelper::FParsedNotifyBindingInfo`  
`struct FParsedNotifyBindingInfo`  
_L20-40_
- desc: Info about the viewmodel and field notify. It can has invalid values and still be a valid OneTime binding.
- L26 _public member_ `const UClass* NotifyFieldClass = nullptr;` — The viewmodel that is used to create the binding. Value is the class of "ViewmodelB" when the path is "ViewmodelA.ViewmodelB.Vector.X"
- L32 _public member_ `FFieldNotificationId NotifyFieldId;` — The property we will bind to Value is "Vector" when the path is "ViewmodelA.ViewmodelB.Vector.X"
- L39 _public member_ `int32 ViewModelIndex = INDEX_NONE;` — The viewmodel index in the original path. When it's INDEX_NONE but the ParsedBindingInfo is valid, the class accessor is the Accessor class. Value 1 when the path is "ViewmodelA.ViewmodelB.Vector.X"

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MVVM` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MVVM` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MVVM` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MVVM` (scope `UE`)
- L14 _namespace_ `namespace FieldPathHelper` (scope `UE::MVVM`)
- L43 _prototype_ `[[nodiscard]] TValueOrError<TArray<FMVVMConstFieldVariant>, FText> GenerateFieldPathList(const UClass* From, FStringView FieldPath, bool bForSourceBinding);` (scope `UE::MVVM::FieldPathHelper`)
- L46 _prototype_ `[[nodiscard]] TValueOrError<TArray<FMVVMConstFieldVariant>, FText> GenerateFieldPathList(TArrayView<const FMVVMConstFieldVariant> Fields, bool bForSourceBinding);` (scope `UE::MVVM::FieldPathHelper`)
- L53 _prototype_ `[[nodiscard]] TValueOrError<FParsedNotifyBindingInfo, FText> GetNotifyBindingInfoFromFieldPath(const UClass* Accessor, TArrayView<const FMVVMConstFieldVariant> Fields);` (scope `UE::MVVM::FieldPathHelper`) — Generate the FParsedNotifyBindingInfo from the parsed field path. This gives us which FieldId and Viewmodel that will be used by the path. Note. The code may have changed since the binding was created in the editor. As an example, a sub-object can be a viewmodel now.
- L56 _prototype_ `[[nodiscard]] FString ToString(TArrayView<const FMVVMFieldVariant> Fields);` (scope `UE::MVVM::FieldPathHelper`)
- L57 _prototype_ `[[nodiscard]] FString ToString(TArrayView<const FMVVMConstFieldVariant> Fields);` (scope `UE::MVVM::FieldPathHelper`)
- L58 _prototype_ `[[nodiscard]] FText ToText(TArrayView<const FMVVMFieldVariant> Fields);` (scope `UE::MVVM::FieldPathHelper`)
- L59 _prototype_ `[[nodiscard]] FText ToText(TArrayView<const FMVVMConstFieldVariant> Fields);` (scope `UE::MVVM::FieldPathHelper`)
- L62 _prototype_ `[[nodiscard]] TValueOrError<UObject*, void> EvaluateObjectProperty(const FFieldContext& InSource);` (scope `UE::MVVM::FieldPathHelper`) — Returns the object value from the FieldContext.
- L70 _prototype_ `[[nodiscard]] TValueOrError<const UStruct*, void> GetFieldAsContainer(const UE::MVVM::FMVVMConstFieldVariant Field);` (scope `UE::MVVM::FieldPathHelper`) — Returns the container that the field represents. If the field is a Object property, then returns the PropertyClass. If the field is a Struct property, then returns the Struct. If the field is a Function, then returns the return value property's container.
- L77 _prototype_ `[[nodiscard]] const UWidgetBlueprintGeneratedClass* GetComponentPropertyPathSource(TArray<UE::MVVM::FMVVMConstFieldVariant> ComponentPaths, const UWidgetBlueprintGeneratedClass* Accessor);` (scope `UE::MVVM::FieldPathHelper`) — Returns the generated widget blueprint class of the widget that owns this component. Accessor: the widget blueprint class that owns the binding. ComponentPaths: The path to a field on a component.

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Debugging/MVVMDebugging.h` (Public)


#### class `UE::MVVM::FDebugging`  
`class FDebugging`  
_L25-98_
- L54 _public prototype_ `DECLARE_EVENT_TwoParams(FDebugging, FViewConstructed, const FView&, const FViewConstructedArgs&);`
- L56 _public member_ `static FViewConstructed OnViewConstructed;` — Broadcast when a view is created and the viewmodels are instantiated and the binding are not registered.
- L57 _public prototype_ `static void BroadcastViewConstructed(const UMVVMView* View);`
- L64 _public prototype_ `DECLARE_EVENT_TwoParams(FDebugging, FViewDestructing, const FView&, const FViewBeginDestructionArgs&);`
- L66 _public member_ `static FViewDestructing OnViewBeginDestruction;` — Broadcast before a view is destroyed.
- L67 _public prototype_ `static void BroadcastViewBeginDestruction(const UMVVMView* View);`
- L77 _public prototype_ `DECLARE_EVENT_TwoParams(FDebugging, FViewSourceValueChanged, const FView&, const FViewSourceValueArgs&);`
- L79 _public member_ `static FViewSourceValueChanged OnViewSourceValueChanged;` — Broadcast when a source changes.
- L80 _public prototype_ `static void BroadcastViewSourceValueChanged(const UMVVMView* View, const FMVVMViewClass_SourceKey ClassSourceKey, const FMVVMView_SourceKey ViewSourceKey);`
- L92 _public prototype_ `DECLARE_EVENT_TwoParams(FDebugging, FLibraryBindingExecuted, const FView&, const FLibraryBindingExecutedArgs&);`
- L94 _public member_ `static FLibraryBindingExecuted OnLibraryBindingExecuted;` — Broadcast when a registered field is modified and a binding need to execute.
- L95 _public prototype_ `static void BroadcastLibraryBindingExecuted(const UMVVMView* View, const FLibraryBindingExecutedArgs& Args);`
- L96 _public prototype_ `static void BroadcastLibraryBindingExecuted(const UMVVMView* View, FMVVMViewClass_BindingKey Binding);`
- L97 _public prototype_ `static void BroadcastLibraryBindingExecuted(const UMVVMView* View, FMVVMViewClass_BindingKey Binding, FMVVMCompiledBindingLibrary::EExecutionFailingReason Result);`

#### struct `UE::MVVM::FDebugging::FView`  
`struct FView`  
_L28-48_
- L31 _public prototype_ `FView() = default;`
- L32 _public prototype_ `FView(const UMVVMView* View);`
- L33 _public prototype_ `FView(const UUserWidget* UserWidget, const UMVVMView* View);`
- L36 _public function_ `const UUserWidget* GetUserWidget() const`
- L41 _public function_ `const UMVVMView* GetView() const`
- L46 _private member_ `const UUserWidget* UserWidget = nullptr;`
- L47 _private member_ `const UMVVMView* View = nullptr;`

#### struct `UE::MVVM::FDebugging::FViewConstructedArgs`  
`struct FViewConstructedArgs`  
_L50-52_

#### struct `UE::MVVM::FDebugging::FViewBeginDestructionArgs`  
`struct FViewBeginDestructionArgs`  
_L60-62_

#### struct `UE::MVVM::FDebugging::FViewSourceValueArgs`  
`struct FViewSourceValueArgs`  
_L70-75_
- L72 _public prototype_ `FViewSourceValueArgs(const FMVVMViewClass_SourceKey& Class, const FMVVMView_SourceKey& View);`
- L73 _public member_ `FMVVMViewClass_SourceKey ClassSource;`
- L74 _public member_ `FMVVMView_SourceKey ViewSource;`

#### struct `UE::MVVM::FDebugging::FLibraryBindingExecutedArgs`  
`struct FLibraryBindingExecutedArgs`  
_L83-89_
- L85 _public prototype_ `FLibraryBindingExecutedArgs(FMVVMViewClass_BindingKey Binding);`
- L86 _public prototype_ `FLibraryBindingExecutedArgs(FMVVMViewClass_BindingKey Binding, FMVVMCompiledBindingLibrary::EExecutionFailingReason Result);`
- L87 _public member_ `FMVVMViewClass_BindingKey Binding;`
- L88 _public member_ `TOptional<FMVVMCompiledBindingLibrary::EExecutionFailingReason> FailingReason;`

#### class `UE::MVVM::FDebugging`  
`class FDebugging`  
_L106-108_
- L54 _public prototype_ `DECLARE_EVENT_TwoParams(FDebugging, FViewConstructed, const FView&, const FViewConstructedArgs&);`
- L56 _public member_ `static FViewConstructed OnViewConstructed;` — Broadcast when a view is created and the viewmodels are instantiated and the binding are not registered.
- L57 _public prototype_ `static void BroadcastViewConstructed(const UMVVMView* View);`
- L64 _public prototype_ `DECLARE_EVENT_TwoParams(FDebugging, FViewDestructing, const FView&, const FViewBeginDestructionArgs&);`
- L66 _public member_ `static FViewDestructing OnViewBeginDestruction;` — Broadcast before a view is destroyed.
- L67 _public prototype_ `static void BroadcastViewBeginDestruction(const UMVVMView* View);`
- L77 _public prototype_ `DECLARE_EVENT_TwoParams(FDebugging, FViewSourceValueChanged, const FView&, const FViewSourceValueArgs&);`
- L79 _public member_ `static FViewSourceValueChanged OnViewSourceValueChanged;` — Broadcast when a source changes.
- L80 _public prototype_ `static void BroadcastViewSourceValueChanged(const UMVVMView* View, const FMVVMViewClass_SourceKey ClassSourceKey, const FMVVMView_SourceKey ViewSourceKey);`
- L92 _public prototype_ `DECLARE_EVENT_TwoParams(FDebugging, FLibraryBindingExecuted, const FView&, const FLibraryBindingExecutedArgs&);`
- L94 _public member_ `static FLibraryBindingExecuted OnLibraryBindingExecuted;` — Broadcast when a registered field is modified and a binding need to execute.
- L95 _public prototype_ `static void BroadcastLibraryBindingExecuted(const UMVVMView* View, const FLibraryBindingExecutedArgs& Args);`
- L96 _public prototype_ `static void BroadcastLibraryBindingExecuted(const UMVVMView* View, FMVVMViewClass_BindingKey Binding);`
- L97 _public prototype_ `static void BroadcastLibraryBindingExecuted(const UMVVMView* View, FMVVMViewClass_BindingKey Binding, FMVVMCompiledBindingLibrary::EExecutionFailingReason Result);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_WITH_MVVM_DEBUGGING (!(UE_BUILD_SHIPPING || UE_BUILD_TEST)) || WITH_EDITOR`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MVVM` (scope `UE`)
- L54 _delegate_ `DECLARE_EVENT_TwoParams(FDebugging, FViewConstructed, const FView&, const FViewConstructedArgs&);`
- L64 _delegate_ `DECLARE_EVENT_TwoParams(FDebugging, FViewDestructing, const FView&, const FViewBeginDestructionArgs&);`
- L77 _delegate_ `DECLARE_EVENT_TwoParams(FDebugging, FViewSourceValueChanged, const FView&, const FViewSourceValueArgs&);`
- L92 _delegate_ `DECLARE_EVENT_TwoParams(FDebugging, FLibraryBindingExecuted, const FView&, const FLibraryBindingExecutedArgs&);`
- L104 _namespace_ `namespace UE`
- L104 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Extensions/MVVMViewClassExtension.h` (Public)


#### class `UMVVMViewExtension`  
`class UMVVMViewExtension : public UObject`  
_L19-28_
- reflection: `UCLASS(MinimalAPI, Within=MVVMView)`
- inherits: `UObject`
- desc: A runtime extension class instance. This information is per instance of a UMVVMViewClassExtension
- L24 _protected function_ `UMVVMView* GetView() const`

#### class `UMVVMViewClassExtension`  
`class UMVVMViewClassExtension : public UObject`  
_L35-54_
- reflection: `UCLASS(MinimalAPI, Within=MVVMViewClass)`
- inherits: `UObject`
- desc: A runtime extension class to define MVVM-related properties and behavior. This information comes from the corresponding UMVVMBlueprintViewExtension class. This class provides a hook into the MVVM runtime initializations.
- L43 _public function_ `virtual UMVVMViewExtension* ViewConstructed(UUserWidget* UserWidget, UMVVMView* View)` — When the view is constructed. The class extension can create a view instance if needed or return nullptr.
- L47 _public function_ `virtual void OnSourcesInitialized(UUserWidget* UserWidget, UMVVMView* View, UMVVMViewExtension* Extension)`
- L48 _public function_ `virtual void OnBindingsInitialized(UUserWidget* UserWidget, UMVVMView* View, UMVVMViewExtension* Extension)`
- L49 _public function_ `virtual void OnEventsInitialized(UUserWidget* UserWidget, UMVVMView* View, UMVVMViewExtension* Extension)`
- L50 _public function_ `virtual void OnEventsUninitialized(UUserWidget* UserWidget, UMVVMView* View, UMVVMViewExtension* Extension)`
- L51 _public function_ `virtual void OnBindingsUninitialized(UUserWidget* UserWidget, UMVVMView* View, UMVVMViewExtension* Extension)`
- L52 _public function_ `virtual void OnSourcesUninitialized(UUserWidget* UserWidget, UMVVMView* View, UMVVMViewExtension* Extension)`
- L53 _public function_ `virtual void OnViewDestructed(UUserWidget* UserWidget, UMVVMView* View, UMVVMViewExtension* Extension)`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Extensions/MVVMViewListViewBaseExtension.h` (Public)


#### class `UMVVMViewListViewBaseClassExtension`  
`class UMVVMViewListViewBaseClassExtension : public UMVVMViewClassExtension`  
_L17-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMViewClassExtension`
- L23 _public prototype_ `virtual void OnSourcesInitialized(UUserWidget* UserWidget, UMVVMView* View, UMVVMViewExtension* Extension) override;`
- L24 _public prototype_ `virtual void OnSourcesUninitialized(UUserWidget* UserWidget, UMVVMView* View, UMVVMViewExtension* Extension) override;`
- L41 _public prototype_ `void Initialize(FInitListViewBaseExtensionArgs InArgs);`
- L44 _public function_ `FName GetEntryViewModelName() const`
- L50 _private prototype_ `void HandleSetViewModelOnEntryWidget(UUserWidget& EntryWidget, UUserWidget* OwningUserWidget, UListViewBase* ListWidget, FName EntryViewmodelName);`
- L54 _private member_ `FName WidgetName;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM Extension")`
- L57 _private member_ `FName EntryViewModelName;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM Extension")`
- L60 _private member_ `FMVVMVCompiledFieldPath WidgetPath;` — `UPROPERTY()`
- L62 _private member_ `TMap<FObjectKey, TWeakObjectPtr<UListViewBase>> CachedListViewWidgets;`

#### struct `UMVVMViewListViewBaseClassExtension::FInitListViewBaseExtensionArgs`  
`struct FInitListViewBaseExtensionArgs`  
_L28-39_
- L30 _public function_ `FInitListViewBaseExtensionArgs(FName InWidgetName, FName InEntryViewModelName, const FMVVMVCompiledFieldPath& InWidgetPath) : WidgetName(InWidgetName), EntryViewModelName(InEntryViewModelName), WidgetPath(InWidgetPath)`
- L36 _public member_ `FName WidgetName;`
- L37 _public member_ `FName EntryViewModelName;`
- L38 _public member_ `FMVVMVCompiledFieldPath WidgetPath;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Extensions/MVVMViewPanelWidgetExtension.h` (Public)


#### class `UMVVMPanelWidgetViewExtension`  
`class UMVVMPanelWidgetViewExtension : public UMVVMViewExtension`  
_L17-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMViewExtension`
- L22 _public prototype_ `void Initialize(UMVVMViewPanelWidgetClassExtension* ClassExtension, UPanelWidget* PanelWidget);`
- L25 _public prototype_ `void BP_SetItems(const TArray<UObject*>& InItems);` — `UFUNCTION(BlueprintCallable, Category = PanelWidget, meta = (AllowPrivateAccess = true, DisplayName = "Set Items", ViewmodelBlueprintWidgetExtension = "EntryViewModel"))`
- L27 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemsChanged);`
- L30 _public member_ `FOnItemsChanged OnItemsChanged;` — `UPROPERTY(BlueprintAssignable)`
- L33 _private prototype_ `void SetViewModelOnEntryWidget(UUserWidget* EntryWidget, UObject* ViewModelObject, UUserWidget* OwningUserWidget);`
- L34 _private prototype_ `void ReplaceAllSlots(TArrayView<TTuple<UPanelSlot*, UWidget*>> NewSlots);`
- L35 _private prototype_ `UUserWidget* GetUserWidget() const;`
- L39 _private member_ `TObjectPtr<UPanelWidget> PanelWidget;` — `UPROPERTY(Transient)`
- L42 _private member_ `TObjectPtr<UMVVMViewPanelWidgetClassExtension> ClassExtension;` — `UPROPERTY(Transient)`

#### class `UMVVMViewPanelWidgetClassExtension`  
`class UMVVMViewPanelWidgetClassExtension : public UMVVMViewClassExtension`  
_L46-129_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMViewClassExtension`
- L52 _public prototype_ `virtual UMVVMViewExtension* ViewConstructed(UUserWidget* UserWidget, UMVVMView* View) override;`
- L53 _public prototype_ `virtual void OnViewDestructed(UUserWidget* UserWidget, UMVVMView* View, UMVVMViewExtension* Extension) override;`
- L78 _public prototype_ `void Initialize(FInitPanelWidgetExtensionArgs InArgs);`
- L83 _public function_ `FName GetWidgetName() const`
- L88 _public function_ `FName GetEntryViewModelName() const`
- L93 _public function_ `UPanelSlot* GetSlotTemplate() const`
- L98 _public function_ `TSubclassOf<UUserWidget> GetEntryWidgetClass() const`
- L103 _public function_ `UClass* GetEntryViewModelClass() const`
- L110 _private member_ `FName WidgetName;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM Extension")`
- L113 _private member_ `FName EntryViewModelName;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM Extension")`
- L116 _private member_ `TSubclassOf<UUserWidget> EntryWidgetClass;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM Extension")`
- L119 _private member_ `TObjectPtr<UPanelSlot> SlotTemplate;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM Extension")`
- L122 _private member_ `FName PanelPropertyName;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM Extension")`
- L125 _private member_ `TObjectPtr<UClass> EntryViewModelClass;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM Extension")`
- L128 _private member_ `FMVVMVCompiledFieldPath WidgetPath;` — `UPROPERTY()`

#### struct `UMVVMViewPanelWidgetClassExtension::FInitPanelWidgetExtensionArgs`  
`struct FInitPanelWidgetExtensionArgs`  
_L57-76_
- L59 _public function_ `FInitPanelWidgetExtensionArgs(FName InWidgetName, FName InEntryViewModelName, const FMVVMVCompiledFieldPath& InWidgetPath, const TSubclassOf<UUserWidget>& InEntryWidgetClass, UPanelSlot* InSlotTemplate, FName InPanelPropertyName, UClass* InEntryViewModelClass) : WidgetName(InWidgetName), EntryViewModelName(InEntryViewModelName), WidgetPath(InWidgetPath), EntryWidgetClass(InEntryWidgetClass), SlotTemplate(InSlotTemplate), PanelPropertyName(InPanelPropertyName), EntryViewModelClass(InEntryViewModelClass)`
- L69 _public member_ `FName WidgetName;`
- L70 _public member_ `FName EntryViewModelName;`
- L71 _public member_ `FMVVMVCompiledFieldPath WidgetPath;`
- L72 _public member_ `TSubclassOf<UUserWidget> EntryWidgetClass;`
- L73 _public member_ `TObjectPtr<UPanelSlot> SlotTemplate;`
- L74 _public member_ `FName PanelPropertyName;`
- L75 _public member_ `TObjectPtr<UClass> EntryViewModelClass;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`
- L27 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemsChanged);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/IModelViewViewModelModule.h` (Public)


#### class `IModelViewViewModelModule`  
`class IModelViewViewModelModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void RegisterImplicitConverter(const TSharedRef<FMVVMImplicitConverter>& Converter) = 0;`
- L14 _public prototype_ `virtual void UnregisterImplicitConverter(const TSharedRef<FMVVMImplicitConverter>& Converter) = 0;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/MVVMBlueprintLibrary.h` (Public)


#### class `UMVVMBlueprintLibrary`  
`class UMVVMBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L10-16_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L15 _public prototype_ `static void SetViewModelByClass(UUserWidget* Widget, TScriptInterface<INotifyFieldValueChanged> ViewModel);` — `UFUNCTION(BlueprintCallable, Category="MVVM | Utilities")`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/MVVMGameSubsystem.h` (Public)


#### class `UMVVMGameSubsystem`  
`class UMVVMGameSubsystem : public UGameInstanceSubsystem`  
_L16-34_
- reflection: `UCLASS(MinimalAPI, DisplayName="Viewmodel Game Subsytem")`
- inherits: `UGameInstanceSubsystem`
- L22 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L23 _public prototype_ `virtual void Deinitialize() override;`
- L27 _public function_ `UMVVMViewModelCollectionObject* GetViewModelCollection() const` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L33 _private member_ `TObjectPtr<UMVVMViewModelCollectionObject> ViewModelCollection;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/MVVMMessageLog.h` (Public)


#### class `UE::MVVM::FMessageLog`  
`class FMessageLog : private ::FMessageLog`  
_L20-39_
- inherits: `::FMessageLog`
- L23 _public member_ `static const FName LogName;`
- L25 _public prototype_ `FMessageLog(const UUserWidget* InUserWidget);`
- L29 _public prototype_ `TSharedRef<FTokenizedMessage> Message(EMessageSeverity::Type InSeverity, const FText& InMessage);`
- L30 _public prototype_ `TSharedRef<FTokenizedMessage> Error(const FText& InMessage);`
- L31 _public prototype_ `TSharedRef<FTokenizedMessage> PerformanceWarning(const FText& InMessage);`
- L32 _public prototype_ `TSharedRef<FTokenizedMessage> Warning(const FText& InMessage);`
- L33 _public prototype_ `TSharedRef<FTokenizedMessage> Info(const FText& InMessage);`
- L35 _public prototype_ `void AddBindingToken(TSharedRef<FTokenizedMessage> NewMessage, const UMVVMViewClass* Class, const FMVVMViewClass_Binding& ClassBinding, FMVVMViewClass_BindingKey Key);`
- L38 _private member_ `TWeakObjectPtr<const UUserWidget> UserWidget;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMVVM, Log, All);`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/MVVMSubsystem.h` (Public)


#### class `UMVVMSubsystem`  
`class UMVVMSubsystem : public UEngineSubsystem`  
_L28-113_
- reflection: `UCLASS(MinimalAPI, DisplayName="Viewmodel Engine Subsytem")`
- inherits: `UEngineSubsystem`
- L34 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L35 _public prototype_ `virtual void Deinitialize() override;`
- L39 _public prototype_ `bool K2_CompareFloatValues(EMVVMConditionOperation Operation, float Value, float CompareValue, float CompareMaxValue = 0.0f);` — `UFUNCTION(BlueprintCallable, Category="Viewmodel", meta = (DisplayName = "Compare Float Values"))`
- L42 _public prototype_ `UMVVMView* K2_GetViewFromUserWidget(const UUserWidget* UserWidget) const;` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel", meta = (DisplayName = "Get View From User Widget"))`
- L44 _public prototype_ `static UMVVMView* GetViewFromUserWidget(const UUserWidget* UserWidget);`
- L47 _public prototype_ `bool DoesWidgetTreeContainedWidget(const UWidgetTree* WidgetTree, const UWidget* ViewWidget) const;` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L51 _public prototype_ `TArray<FMVVMAvailableBinding> K2_GetAvailableBindings(const UClass* Class, const UClass* Accessor) const;` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel", meta = (DisplayName = "Get Available Bindings"))` — @return The list of all the AvailableBindings that are available for the Class.
- L53 _public prototype_ `static TArray<FMVVMAvailableBinding> GetAvailableBindings(const UClass* Class, const UClass* Accessor);`
- L59 _public prototype_ `static TArray<FMVVMAvailableBinding> GetAvailableBindingsForStruct(const UScriptStruct* Struct);` — @return The list of all the AvailableBindings that are available from the SriptStuct. @note When FMVVMAvailableBinding::HasNotify is false, a notification can still be triggered by the owner of the struct. The struct changed but which property of the struct changed is unknown.
- L61 _public prototype_ `static TArray<FMVVMAvailableBinding> GetAvailableBindingsForEvent(const UClass* Class, const UClass* Accessor);`
- L65 _public prototype_ `FMVVMAvailableBinding K2_GetAvailableBinding(const UClass* Class, FMVVMBindingName BindingName, const UClass* Accessor) const;` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel", meta = (DisplayName = "Get Available Binding"))` — @return The AvailableBinding from a BindingName.
- L67 _public prototype_ `static FMVVMAvailableBinding GetAvailableBinding(const UClass* Class, FMVVMBindingName BindingName, const UClass* Accessor);`
- L70 _public prototype_ `static FMVVMAvailableBinding GetAvailableBindingForField(UE::MVVM::FMVVMConstFieldVariant Variant, const UClass* Accessor);` — @return The AvailableBinding from a field.
- L72 _public prototype_ `static FMVVMAvailableBinding GetAvailableBindingForEvent(UE::MVVM::FMVVMConstFieldVariant FieldVariant, const UClass* Accessor);`
- L74 _public prototype_ `static FMVVMAvailableBinding GetAvailableBindingForEvent(const UClass* Class, FMVVMBindingName BindingName, const UClass* Accessor);`
- L78 _public prototype_ `UMVVMViewModelCollectionObject* GetGlobalViewModelCollection() const;` — `UE_DEPRECATED(5.3, "GetGlobalViewModelCollection has been deprecated, please use the game instance subsystem.")` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel", meta=(DeprecatedFunction, DeprecatedMessage = "This version of GetGlobalViewModelCollection has been deprecated, please use GetViewModelCollection from the Viewmodel Game subsystem."))`
- L110 _public prototype_ `[[nodiscard]] TValueOrError<bool, FText> IsBindingValid(FConstDirectionalBindingArgs Args) const;`
- L111 _public prototype_ `[[nodiscard]] TValueOrError<bool, FText> IsBindingValid(FDirectionalBindingArgs Args) const;`
- L112 _public prototype_ `[[nodiscard]] TValueOrError<bool, FText> IsBindingValid(FBindingArgs Args) const;`

#### struct `UMVVMSubsystem::FConstDirectionalBindingArgs`  
`struct FConstDirectionalBindingArgs`  
_L80-85_
- L82 _public member_ `UE::MVVM::FMVVMConstFieldVariant SourceBinding;`
- L83 _public member_ `UE::MVVM::FMVVMConstFieldVariant DestinationBinding;`
- L84 _public member_ `const UFunction* ConversionFunction = nullptr;`

#### struct `UMVVMSubsystem::FDirectionalBindingArgs`  
`struct FDirectionalBindingArgs`  
_L87-101_
- L89 _public member_ `UE::MVVM::FMVVMFieldVariant SourceBinding;`
- L90 _public member_ `UE::MVVM::FMVVMFieldVariant DestinationBinding;`
- L91 _public member_ `UFunction* ConversionFunction = nullptr;`
- L93 _public function_ `FConstDirectionalBindingArgs ToConst() const`

#### struct `UMVVMSubsystem::FBindingArgs`  
`struct FBindingArgs`  
_L103-108_
- L105 _public member_ `EMVVMBindingMode Mode = EMVVMBindingMode::OneWayToDestination;`
- L106 _public member_ `FDirectionalBindingArgs ForwardArgs;`
- L107 _public member_ `FDirectionalBindingArgs BackwardArgs;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/MVVMViewModelBase.h` (Public)


#### enum `UMMVVMViewModelBase::(anonymous)`  
``  
_L31-36_

#### class `UMVVMViewModelBase`  
`class UMVVMViewModelBase : public UObject, public INotifyFieldValueChanged`  
_L42-125_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract, DisplayName="MVVM Base Viewmodel", meta=(ShowWorldContextPin="true"))`
- inherits: `UObject,INotifyFieldValueChanged`
- desc: Base class for MVVM viewmodel.
- L54 _public prototype_ `virtual FDelegateHandle AddFieldValueChangedDelegate(UE::FieldNotification::FFieldId InFieldId, FFieldValueChangedDelegate InNewDelegate) override final;`
- L55 _public prototype_ `virtual bool RemoveFieldValueChangedDelegate(UE::FieldNotification::FFieldId InFieldId, FDelegateHandle InHandle) override final;`
- L56 _public prototype_ `virtual int32 RemoveAllFieldValueChangedDelegates(FDelegateUserObjectConst InUserObject) override final;`
- L57 _public prototype_ `virtual int32 RemoveAllFieldValueChangedDelegates(UE::FieldNotification::FFieldId InFieldId, FDelegateUserObjectConst InUserObject) override final;`
- L58 _public prototype_ `virtual const UE::FieldNotification::IClassDescriptor& GetFieldNotificationDescriptor() const override;`
- L59 _public prototype_ `virtual void BroadcastFieldValueChanged(UE::FieldNotification::FFieldId InFieldId) override;`
- L62 _public prototype_ `TArray<UE::FieldNotification::FFieldMulticastDelegate::FDelegateView> GetNotificationDelegateView() const;`
- L65 _public prototype_ `void K2_AddFieldValueChangedDelegate(FFieldNotificationId FieldId, FFieldValueChangedDynamicDelegate Delegate);` — `UFUNCTION(BlueprintCallable, Category = "FieldNotify", meta = (DisplayName = "Add Field Value Changed Delegate", ScriptName = "AddFieldValueChangedDelegate"))`
- L68 _public prototype_ `void K2_RemoveFieldValueChangedDelegate(FFieldNotificationId FieldId, FFieldValueChangedDynamicDelegate Delegate);` — `UFUNCTION(BlueprintCallable, Category = "FieldNotify", meta = (DisplayName = "Remove Field Value Changed Delegate", ScriptName = "RemoveFieldValueChangedDelegate"))`
- L73 _protected prototype_ `void K2_BroadcastFieldValueChanged(FFieldNotificationId FieldId);` — `UE_DEPRECATED(5.3, "BroadcastFieldValueChanged has been deprecated, please use the regular blueprint setter.")` — `UFUNCTION(BlueprintCallable, Category="FieldNotify", meta=(DisplayName="Broadcast Field Value Changed", ScriptName="BroadcastFieldValueChanged", DeprecatedFunction, DeprecatedMessage = "Use the regular setter node."))`
- L77 _protected prototype_ `bool K2_SetPropertyValue(UPARAM(ref) const int32& OldValue, UPARAM(ref) const int32& NewValue);` — `UE_DEPRECATED(5.3, "SetPropertyValue has been deprecated, please use the regular blueprint setter.")` — `UFUNCTION(BlueprintCallable, CustomThunk, Category="Viewmodel", meta=(CustomStructureParam="OldValue,NewValue", ScriptName="SetPropertyValue", DeprecatedFunction, DeprecatedMessage = "Use the regular setter node.", BlueprintInternalUseOnly="true"))`
- L81 _protected function_ `template<typename T, typename U = T> bool SetPropertyValue(T& Value, const U& NewValue, UE::FieldNotification::FFieldId FieldId)` — Set the new value and notify if the property value changed.
- L93 _protected function_ `bool SetPropertyValue(FText& Value, const FText& NewValue, UE::FieldNotification::FFieldId FieldId)`
- L105 _protected function_ `bool SetPropertyValue(TArray<FText>& Value, const TArray<FText>& NewValue, UE::FieldNotification::FFieldId FieldId)`
- L124 _private member_ `UE::MVVM::FMVVMFieldNotificationDelegates NotificationDelegates;`

#### struct `UMVVMViewModelBase::FFieldNotificationClassDescriptor`  
`struct FFieldNotificationClassDescriptor : public ::UE::FieldNotification::IClassDescriptor`  
_L47-50_
- inherits: `::UE::FieldNotification::IClassDescriptor`
- L49 _public prototype_ `virtual void ForEachField(const UClass* Class, TFunctionRef<bool(UE::FieldNotification::FFieldId FielId)> Callback) const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`
- L16 _macro_ `#define UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(MemberName) \` — After a field value changed. Broadcast the event.
- L20 _macro_ `#define UE_MVVM_SET_PROPERTY_VALUE(MemberName, NewValue) \` — If the property value changed then set the new value and notify.
- L24 _macro_ `#define UE_MVVM_SET_PROPERTY_VALUE_INLINE(MemberName, NewValue) \` — Use this version to set property values that can't be captured as a function arguments (i.e. bitfields).
- L27 _namespace_ `namespace UMMVVMViewModelBase`
- L33 _enumerator_ `MVVMAllowedContextCreationType` (scope `UMMVVMViewModelBase::__anon080d31d90103`) — [ClassMetadata] Specifies which ContextCreationType is allowed for that viewmodel. ex: UCLASS(meta=(MVVMAllowedContextCreationType="Manual|CreateInstance"))
- L35 _enumerator_ `MVVMDisallowedContextCreationType` (scope `UMMVVMViewModelBase::__anon080d31d90103`) — [ClassMetadata] Specifies which ContextCreationType is disallowed for that viewmodel, all other type are allowed. ex: UCLASS(meta=(MVVMDisallowedContextCreationType="Manual|CreateInstance"))
- L108 _function_ `` (scope `UMVVMViewModelBase::SetPropertyValue`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMAvailableBinding.h` (Public)


#### struct `FMVVMAvailableBinding`  
`struct FMVVMAvailableBinding`  
_L11-83_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public prototype_ `FMVVMAvailableBinding() = default;`
- L18 _public function_ `explicit FMVVMAvailableBinding(FMVVMBindingName InBindingName, bool bInReadable, bool bInWritable, bool bInHasNotify) : BindingName(InBindingName) , bIsReadable(bInReadable) , bIsWritable(bInWritable) , bHasNotify(bInHasNotify)`
- L28 _public function_ `FMVVMBindingName GetBindingName() const`
- L33 _public function_ `bool HasNotify() const`
- L38 _public function_ `bool IsReadable() const`
- L43 _public function_ `bool IsWritable() const`
- L48 _public function_ `bool IsValid() const`
- L53 _public function_ `bool operator==(const FMVVMAvailableBinding& Other) const`
- L61 _public function_ `bool operator!=(const FMVVMAvailableBinding& Other) const`
- L73 _private member_ `FMVVMBindingName BindingName;` — `UPROPERTY()`
- L76 _private member_ `bool bIsReadable = false;` — `UPROPERTY()`
- L79 _private member_ `bool bIsWritable = false;` — `UPROPERTY()`
- L82 _private member_ `bool bHasNotify = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L66 _function_ `friend int32 GetTypeHash(const FMVVMAvailableBinding& Value)`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMBindingMode.h` (Public)


#### enum `EMVVMBindingMode`  
`enum class EMVVMBindingMode : uint8`  
_L10-17_
- reflection: `UENUM()`
- L12 _public enumerator_ `OneTimeToDestination = 0`
- L13 _public enumerator_ `OneWayToDestination`
- L14 _public enumerator_ `TwoWay`
- L15 _public enumerator_ `OneTimeToSource UMETA(Hidden)`
- L16 _public enumerator_ `OneWayToSource`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MVVM` (scope `UE`)
- L22 _prototype_ `[[nodiscard]] bool IsForwardBinding(EMVVMBindingMode Mode);` (scope `UE::MVVM`)
- L23 _prototype_ `[[nodiscard]] bool IsBackwardBinding(EMVVMBindingMode Mode);` (scope `UE::MVVM`)
- L24 _prototype_ `[[nodiscard]] bool IsOneTimeBinding(EMVVMBindingMode Mode);` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMBindingName.h` (Public)


#### struct `FMVVMBindingName`  
`struct FMVVMBindingName`  
_L9-58_
- reflection: `USTRUCT(BlueprintType)`
- L14 _public prototype_ `FMVVMBindingName() = default;`
- L16 _public function_ `explicit FMVVMBindingName(FName InBindingName) : BindingName(InBindingName)`
- L23 _public function_ `bool IsValid() const`
- L28 _public function_ `FName ToName() const`
- L33 _public function_ `FString ToString() const`
- L38 _public function_ `bool operator== (const FMVVMBindingName& Other) const`
- L43 _public function_ `bool operator!= (const FMVVMBindingName& Other) const`
- L57 _private member_ `FName BindingName;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")` — todo this should be and make helper function to build the name in BP with a picker

#### Free symbols / members of external scopes

- L49 _function_ `friend int32 GetTypeHash(const FMVVMBindingName& Value)`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMConditionOperation.h` (Public)


#### enum `EMVVMConditionOperation`  
`enum class EMVVMConditionOperation : uint8`  
_L10-20_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `Equal`
- L13 _public enumerator_ `NotEqual`
- L14 _public enumerator_ `MoreThan`
- L15 _public enumerator_ `MoreThanOrEqual`
- L16 _public enumerator_ `LessThan`
- L17 _public enumerator_ `LessThanOrEqual`
- L18 _public enumerator_ `BetweenInclusive`
- L19 _public enumerator_ `BetweenExclusive`

#### Free symbols / members of external scopes

- L22 _prototype_ `const TCHAR* LexToString(EMVVMConditionOperation Enum);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMEventField.h` (Public)


#### struct `FMVVMEventField`  
`struct FMVVMEventField`  
_L23-26_
- reflection: `USTRUCT(BlueprintType)`
- desc: Generic structure to notify when an event occurs. class UMyViewmodel : public UMVVMViewModelBase { UPROPERTY(FieldNotify) FMVVMEventField SomeEvent; void OnSomeEvent() { UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(SomeEvent); } }; };

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMExecutionMode.h` (Public)


#### enum `EMVVMExecutionMode`  
`enum class EMVVMExecutionMode : uint8`  
_L10-20_
- reflection: `UENUM()`
- L13 _public enumerator_ `Immediate = 0` — Execute the binding as soon as the source value changes.
- L15 _public enumerator_ `Delayed = 1` — Execute the binding at the end of the frame before drawing when the source value changes.
- L17 _public enumerator_ `Tick = 2` — Always execute the binding at the end of the frame.
- L19 _public enumerator_ `DelayedWhenSharedElseImmediate = 3 UMETA(DisplayName="Auto")` — When the binding can be triggered from multiple fields, use Delayed. Else, uses Immediate.

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMFieldContext.h` (Public)


#### struct `UE::MVVM::FFieldContext`  
`struct FFieldContext : private TPair<UE::MVVM::FObjectVariant, UE::MVVM::FMVVMFieldVariant>`  
_L13-26_
- inherits: `TPair<UE::MVVM::FObjectVariant,UE::MVVM::FMVVMFieldVariant>`
- L18 _public function_ `const UE::MVVM::FObjectVariant& GetObjectVariant() const`
- L22 _public function_ `const UE::MVVM::FMVVMFieldVariant& GetFieldVariant() const`

#### struct `UE::MVVM::FConstFieldContext`  
`struct FConstFieldContext : private TPair<UE::MVVM::FConstObjectVariant, UE::MVVM::FMVVMConstFieldVariant>`  
_L29-42_
- inherits: `TPair<UE::MVVM::FConstObjectVariant,UE::MVVM::FMVVMConstFieldVariant>`
- L34 _public function_ `const UE::MVVM::FConstObjectVariant& GetObjectVariant() const`
- L38 _public function_ `const UE::MVVM::FMVVMConstFieldVariant& GetFieldVariant() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMFieldVariant.h` (Public)


#### struct `UE::MVVM::TMVVMFieldVariant`  
`template<bool bConst> struct TMVVMFieldVariant`  
_L17-193_
- desc: Represents a possibly-const binding to either a UFunction or FProperty
- L21 _private typedef_ `using FunctionType = std::conditional_t<bConst, const UFunction, UFunction>;`
- L22 _private typedef_ `using PropertyType = std::conditional_t<bConst, const FProperty, FProperty>;`
- L36 _public prototype_ `TMVVMFieldVariant() = default;`
- L38 _public function_ `explicit TMVVMFieldVariant(FFieldVariant InVariant)`
- L52 _public function_ `explicit TMVVMFieldVariant(PropertyType* InValue)`
- L58 _public function_ `explicit TMVVMFieldVariant(FunctionType* InValue)`
- L64 _public function_ `[[nodiscard]] bool IsProperty() const`
- L69 _public function_ `[[nodiscard]] PropertyType* GetProperty() const`
- L75 _public function_ `void SetProperty(PropertyType* InValue)`
- L81 _public function_ `[[nodiscard]] bool IsFunction() const`
- L86 _public function_ `[[nodiscard]] FunctionType* GetFunction() const`
- L92 _public function_ `void SetFunction(FunctionType* InValue)`
- L98 _public function_ `[[nodiscard]] FName GetName() const`
- L111 _public function_ `[[nodiscard]] UStruct* GetOwner() const`
- L125 _public function_ `[[nodiscard]] bool HasAnyFlags(EObjectFlags InFlags) const` — `UE_DEPRECATED(5.8, "TMVVMFieldVariant::HasAnyFlags is deprecated, it is only relevant for functions. Consider using GetFunction()->HasAnyFlags() after checking IsFunction() instead.")`
- L134 _public function_ `[[nodiscard]] bool IsValid() const`
- L147 _public function_ `[[nodiscard]] bool IsEmpty() const`
- L152 _public function_ `void Reset()`
- L159 _public function_ `template<bool bOtherConst> bool operator==(const TMVVMFieldVariant<bOtherConst>& B) const`
- L173 _public function_ `template<bool bOtherConst> bool operator!=(const TMVVMFieldVariant<bOtherConst>& B) const`
- L191 _private member_ `VariantType Binding;`
- L192 _private member_ `EVariantType Type = EVariantType::Empty;`

#### union `UE::MVVM::TMVVMFieldVariant::VariantType`  
`union VariantType`  
_L23-27_
- L25 _public member_ `FunctionType* Function = nullptr;`
- L26 _public member_ `PropertyType* Property;`

#### enum `UE::MVVM::TMVVMFieldVariant::EVariantType`  
`enum class EVariantType : uint8`  
_L28-33_
- L30 _public enumerator_ `Empty`
- L31 _public enumerator_ `Function`
- L32 _public enumerator_ `Property`

#### struct `UE::MVVM::FMVVMFieldVariant`  
`struct FMVVMFieldVariant : public TMVVMFieldVariant<false>`  
_L196-201_
- inherits: `TMVVMFieldVariant<false>`

#### struct `UE::MVVM::FMVVMConstFieldVariant`  
`struct FMVVMConstFieldVariant : public TMVVMFieldVariant<true>`  
_L204-227_
- inherits: `TMVVMFieldVariant<true>`
- L210 _public function_ `FMVVMConstFieldVariant(const FMVVMFieldVariant& OtherVariant)`
- L222 _public function_ `FMVVMConstFieldVariant& operator=(const FMVVMFieldVariant& OtherVariant)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MVVM` (scope `UE`)
- L178 _function_ `friend int32 GetTypeHash(const TMVVMFieldVariant<bConst>& Variant)` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMFunctionContext.h` (Public)


#### struct `UE::MVVM::TFunctionContext`  
`template<bool bConst> struct TFunctionContext`  
_L14-61_
- L16 _public typedef_ `using ObjectType = std::conditional_t<bConst, const UObject*, UObject*>;`
- L17 _public typedef_ `using FunctionType = std::conditional_t<bConst, const UFunction*, UFunction*>;`
- L20 _public prototype_ `TFunctionContext() = default;`
- L21 _public function_ `TFunctionContext(ObjectType InObject, FunctionType InFunction) : ObjectPtr(InObject) , FunctionPtr(InFunction)`
- L31 _public function_ `[[nodiscard]] ObjectType GetObject() const`
- L36 _public function_ `[[nodiscard]] FunctionType GetFunction() const`
- L41 _public function_ `void Reset()`
- L47 _public function_ `template<bool bOtherConst> bool operator==(const TFunctionContext<bOtherConst>& Other) const`
- L53 _public function_ `template<bool bOtherConst> bool operator!=(const TObjectVariant<bOtherConst>& Other) const`
- L59 _private member_ `ObjectType ObjectPtr = nullptr;`
- L60 _private member_ `FunctionType FunctionPtr = nullptr;`

#### struct `UE::MVVM::FFunctionContext`  
`struct FFunctionContext : public TFunctionContext<false>`  
_L64-76_
- inherits: `TFunctionContext<false>`
- L70 _public function_ `static FFunctionContext MakeStaticFunction(FunctionType InFunction)`

#### struct `UE::MVVM::FConstFunctionContext`  
`struct FConstFunctionContext : public TFunctionContext<true>`  
_L79-101_
- inherits: `TFunctionContext<true>`
- L85 _public function_ `FConstFunctionContext(const FFunctionContext& Other) : TFunctionContext<true>(Other.GetObject(), Other.GetFunction())`
- L90 _public function_ `static FConstFunctionContext MakeStaticFunction(FunctionType InFunction)`
- L96 _public function_ `FConstFunctionContext& operator=(const FFunctionContext& Other)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MVVM` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMObjectVariant.h` (Public)


#### struct `UE::MVVM::TObjectVariant`  
`template<bool bConst> struct TObjectVariant`  
_L16-194_
- L21 _private typedef_ `using ContainerType = std::conditional_t<bConst, const void*, void*>;`
- L64 _private typedef_ `using UScriptStructType = FScriptStructStackedContainer;`
- L65 _private typedef_ `using UObjectType = std::conditional_t<bConst, const UObject, UObject>;`
- L66 _private typedef_ `using VariantType = TVariant<FEmptyVariantState, UScriptStructType, UObjectType*>;`
- L69 _public prototype_ `TObjectVariant() = default;`
- L71 _public function_ `explicit TObjectVariant(UObjectType* InValue)`
- L76 _public function_ `explicit TObjectVariant(const UScriptStruct* InScriptStruct, ContainerType InValue)`
- L81 _public function_ `[[nodiscard]] bool IsUObject() const`
- L86 _public function_ `[[nodiscard]] UObjectType* GetUObject() const`
- L91 _public function_ `[[nodiscard]] const UClass* GetUClass() const`
- L97 _public function_ `void SetUObject(UObjectType* InValue)`
- L102 _public function_ `[[nodiscard]] bool IsUScriptStruct() const`
- L107 _public function_ `[[nodiscard]] ContainerType GetUScriptStructData() const`
- L112 _public function_ `[[nodiscard]] const UScriptStruct* GetUScriptStruct() const`
- L117 _public function_ `void SetUScriptStruct(const UScriptStruct* InScriptStruct, ContainerType InValue)`
- L122 _public function_ `[[nodiscard]] ContainerType GetData() const`
- L127 _public function_ `[[nodiscard]] const UStruct* GetOwner() const`
- L140 _public function_ `[[nodiscard]] bool IsEmpty() const`
- L145 _public function_ `[[nodiscard]] bool IsNull() const`
- L150 _public function_ `void Reset()`
- L156 _public function_ `template<bool bOtherConst> bool operator==(const TObjectVariant<bOtherConst>& B) const`
- L174 _public function_ `template<bool bOtherConst> bool operator!=(const TObjectVariant<bOtherConst>& B) const`
- L193 _private member_ `VariantType Binding;`

#### struct `UE::MVVM::TObjectVariant::FScriptStructStackedContainer`  
`struct FScriptStructStackedContainer`  
_L23-31_
- L25 _public prototype_ `FScriptStructStackedContainer() = default;`
- L26 _public function_ `FScriptStructStackedContainer(const UScriptStruct* InScriptStruct, ContainerType InContainer) : ScriptStruct(InScriptStruct), Container(InContainer)`
- L29 _public member_ `const UScriptStruct* ScriptStruct = nullptr;`
- L30 _public member_ `ContainerType Container = nullptr;`

#### struct `UE::MVVM::TObjectVariant::FScriptStructAllocatedContainer`  
`struct FScriptStructAllocatedContainer`  
_L33-62_
- L35 _public prototype_ `FScriptStructAllocatedContainer() = default;`
- L36 _public prototype_ `FScriptStructAllocatedContainer(const FScriptStructAllocatedContainer&) = delete;`
- L37 _public prototype_ `FScriptStructAllocatedContainer& operator=(const FScriptStructAllocatedContainer&) = delete;`
- L39 _public function_ `FScriptStructAllocatedContainer(const UScriptStruct* InScriptStruct) : ScriptStruct(InScriptStruct), Container(nullptr)`
- L48 _public function_ `~FScriptStructAllocatedContainer()`
- L60 _public member_ `TWeakObjectPtr<const UScriptStruct> ScriptStruct = nullptr;`
- L61 _public member_ `ContainerType Container = nullptr;`

#### struct `UE::MVVM::FObjectVariant`  
`struct FObjectVariant : public TObjectVariant<false>`  
_L197-202_
- inherits: `TObjectVariant<false>`

#### struct `UE::MVVM::FConstObjectVariant`  
`struct FConstObjectVariant : public TObjectVariant<true>`  
_L205-228_
- inherits: `TObjectVariant<true>`
- L211 _public function_ `FConstObjectVariant(const FObjectVariant& OtherVariant)`
- L223 _public function_ `FConstObjectVariant& operator=(const FObjectVariant& OtherVariant)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MVVM` (scope `UE`)
- L179 _function_ `friend int32 GetTypeHash(const TObjectVariant<bConst>& Variant)` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMViewModelCollection.h` (Public)


#### struct `FMVVMViewModelCollection`  
`struct FMVVMViewModelCollection`  
_L15-39_
- reflection: `USTRUCT()`
- L20 _public prototype_ `UMVVMViewModelBase* FindViewModelInstance(FMVVMViewModelContext Context) const;`
- L21 _public prototype_ `UMVVMViewModelBase* FindFirstViewModelInstanceOfType(const TSubclassOf<UMVVMViewModelBase>& ViewModelClass) const;`
- L23 _public prototype_ `bool AddInstance(FMVVMViewModelContext Context, UMVVMViewModelBase* ViewModel);`
- L24 _public prototype_ `bool RemoveInstance(FMVVMViewModelContext Context);`
- L25 _public prototype_ `int32 RemoveAllInstances(UMVVMViewModelBase* ViewModel);`
- L27 _public prototype_ `void Reset();`
- L29 _public function_ `FSimpleMulticastDelegate& OnCollectionChanged()`
- L36 _private member_ `mutable TArray<FMVVMViewModelContextInstance> ViewModelInstances;` — `UPROPERTY()`
- L38 _private member_ `FSimpleMulticastDelegate OnCollectionChangedDelegate;`

#### class `UMVVMViewModelCollectionObject`  
`class UMVVMViewModelCollectionObject : public UObject`  
_L44-91_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "MVVM View Model Collection Object"))`
- inherits: `UObject`
- L50 _public function_ `UMVVMViewModelBase* FindViewModelInstance(FMVVMViewModelContext Context) const` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L60 _public function_ `UMVVMViewModelBase* FindFirstViewModelInstanceOfType(const TSubclassOf<UMVVMViewModelBase>& ViewModelClass) const` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")` — Finds a View Model of the given type. If the collection contains multiple instances of the same type then this will return the first one found.
- L66 _public function_ `bool AddViewModelInstance(FMVVMViewModelContext Context, UMVVMViewModelBase* ViewModel)` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L72 _public function_ `bool RemoveViewModel(FMVVMViewModelContext Context)` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L78 _public function_ `int32 RemoveAllViewModelInstance(UMVVMViewModelBase* ViewModel)` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L83 _public function_ `FSimpleMulticastDelegate& OnCollectionChanged()`
- L90 _private member_ `FMVVMViewModelCollection ViewModelCollection;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMViewModelContext.h` (Public)


#### struct `FMVVMViewModelContext`  
`struct FMVVMViewModelContext`  
_L16-33_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `TSubclassOf<UMVVMViewModelBase> ContextClass;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Viewmodel")`
- L25 _public member_ `FName ContextName;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Viewmodel")`
- L28 _public prototype_ `bool IsValid() const;`
- L29 _public prototype_ `bool operator== (const FMVVMViewModelContext& Other) const;`
- L30 _public prototype_ `bool IsCompatibleWith(const FMVVMViewModelContext& Other) const;`
- L31 _public prototype_ `bool IsCompatibleWith(const TSubclassOf<UMVVMViewModelBase>& OtherClass) const;`
- L32 _public prototype_ `bool IsCompatibleWith(const UMVVMViewModelBase* Other) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/Types/MVVMViewModelContextInstance.h` (Public)


#### struct `FMVVMViewModelContextInstance`  
`struct FMVVMViewModelContextInstance`  
_L14-57_
- reflection: `USTRUCT()`
- L19 _public prototype_ `FMVVMViewModelContextInstance() = default;`
- L20 _public function_ `FMVVMViewModelContextInstance(FMVVMViewModelContext InContext, UMVVMViewModelBase* InInstance) : Context(InContext) , Instance(InInstance)`
- L31 _public function_ `bool IsValid() const`
- L36 _public function_ `FMVVMViewModelContext GetContext() const`
- L41 _public function_ `UMVVMViewModelBase* GetViewModel()`
- L46 _public function_ `const UMVVMViewModelBase* GetViewModel() const`
- L53 _private member_ `FMVVMViewModelContext Context;` — `UPROPERTY()`
- L56 _private member_ `TObjectPtr<UMVVMViewModelBase> Instance = nullptr;` — `UPROPERTY()`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/View/MVVMView.h` (Public)


#### struct `FMVVMView_Source`  
`struct FMVVMView_Source`  
_L31-62_
- reflection: `USTRUCT()`
- desc: Instance FMVVMViewClass_Source for the UUserWdiget
- L37 _public member_ `TObjectPtr<UObject> Source;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — The source object. The source implement the INotifyFieldValueChanged interface.
- L41 _public member_ `FMVVMViewClass_SourceKey ClassKey;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — The key of this source in the ViewClass.
- L45 _public member_ `int32 RegisteredCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — Number of bindings connected to the source.
- L49 _public member_ `bool bSourceInitialized = false;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — The source is created.
- L53 _public member_ `bool bBindingsInitialized = false;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — The source bindings are initialized.
- L57 _public member_ `bool bSetManually = false;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — The source was set manually via SetViewModel.
- L61 _public member_ `bool bAssignedToUserWidgetProperty = false;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — The source was set to a UserWidget property.

#### class `UMVVMView`  
`class UMVVMView : public UUserWidgetExtension`  
_L68-289_
- reflection: `UCLASS(MinimalAPI, Transient, DisplayName="MVVM View")`
- inherits: `UUserWidgetExtension`
- desc: Instance UMVVMClassExtension_View for the UUserWidget
- L73 _public prototype_ `void ConstructView(const UMVVMViewClass* InGeneratedViewClass);`
- L77 _public prototype_ `virtual void Construct() override;` — virtual void Initialize() override;
- L78 _public prototype_ `virtual void Destruct() override;`
- L82 _public function_ `bool IsConstructed() const` — Is the view in a valid constructed state?
- L93 _public prototype_ `void InitializeSources();` — `UFUNCTION(BlueprintCallable, Category = "View")` — Initialize the sources if they are not already initialized. Initializing the sources will also initialize the bindings if the option bInitializeBindingsOnConstruct is enabled. @note A sources can be a viewmodel or any other object used by a binding.
- L99 _public prototype_ `void UninitializeSources();` — `UFUNCTION(BlueprintCallable, Category = "View")` — Uninitialize the sources if they are already initialized. It will uninitialized the bindings.
- L102 _public function_ `bool AreSourcesInitialized() const` — `UFUNCTION(BlueprintPure, Category = "View")` — The sources were initialized, manually or automatically.
- L112 _public prototype_ `void InitializeBindings();` — `UFUNCTION(BlueprintCallable, Category = "View")` — Initialize the bindings if they are not already initialized. Initializing the bindings will execute them.
- L115 _public prototype_ `void UninitializeBindings();` — `UFUNCTION(BlueprintCallable, Category = "View")` — Uninitialize the bindings if they are already initialized.
- L118 _public function_ `bool AreBindingsInitialized() const` — `UFUNCTION(BlueprintPure, Category = "View")` — The bindings were initialized, manually or automatically.
- L125 _public prototype_ `void InitializeEvents();` — `UFUNCTION(BlueprintCallable, Category = "View")` — Initialize the events if they are not already initialized.
- L128 _public prototype_ `void UninitializeEvents();` — `UFUNCTION(BlueprintCallable, Category = "View")` — Uninitialize the events if they are already initialized.
- L131 _public function_ `bool AreEventsInitialized() const` — `UFUNCTION(BlueprintPure, Category = "View")` — The events were initialized, manually or automatically.
- L137 _public function_ `const UMVVMViewClass* GetViewClass() const` — The shared information for each instance of the view.
- L143 _public function_ `const TArrayView<const FMVVMView_Source> GetSources() const` — The list of the sources needed by the view.
- L149 _public function_ `const FMVVMView_Source& GetSource(FMVVMView_SourceKey Key) const` — The source used by the view.
- L155 _public prototype_ `void ExecuteDelayedBinding(const FMVVMViewClass_BindingKey& DelayedBinding) const;`
- L156 _public prototype_ `void ExecuteTickBindings() const;`
- L160 _public prototype_ `TScriptInterface<INotifyFieldValueChanged> GetViewModel(FName ViewModelName) const;` — `UFUNCTION(BlueprintCallable, Category = "View")` — Find and return the viewmodel with the specified name.
- L168 _public prototype_ `bool SetViewModel(FName ViewModelName, TScriptInterface<INotifyFieldValueChanged> ViewModel);` — `UFUNCTION(BlueprintCallable, Category = "View")` — Set the viewmodel of the specified name. The viewmodel needs to be settable and the type should match (child of the defined viewmodel). If the view is initialized, all bindings that uses that viewmodel will be re-executed with the new viewmodel instance.
- L176 _public prototype_ `bool SetViewModelByClass(TScriptInterface<INotifyFieldValueChanged> NewValue);` — `UFUNCTION(BlueprintCallable, Category = "View")` — Set the first viewmodel matching the exact specified type. If none is found, set the first viewmodel matching a child of the specified type The viewmodel needs to be settable and it should have a valid name. If the view is initialized, all bindings that uses that viewmodel will be re-executed with the new viewmodel instance.
- L182 _public prototype_ `bool ExecuteViewModelBindings(FName ViewModelName);` — `UFUNCTION(BlueprintCallable, Category = "View")` — Execute all the bindings that use the viewmodel.
- L191 _private prototype_ `bool AreSourcesValidForEvent(int32 EventKey) const;` — `UFUNCTION(BlueprintCallable, Category = "View", meta=(BlueprintInternalUseOnly="true"))` — Set the viewmodel of the specified name. The viewmodel needs to be settable and the type should match (child of the defined viewmodel). If the view is initialized, all bindings that uses that viewmodel will be re-executed with the new viewmodel instance.
- L198 _private prototype_ `bool AreSourcesValidForBinding(int32 BindingKey) const;` — `UFUNCTION(BlueprintCallable, Category = "View", meta = (BlueprintInternalUseOnly = "true"))` — Checks if all source bindings (Src / Dst objects) are valid for a binding Currently used to verify if after effects of async conversion functions are safe to trigger.
- L202 _private prototype_ `void InitializeSource(FMVVMView_SourceKey SourceKey);`
- L203 _private prototype_ `void InitializeSourceInternal(UObject* NewSource, FMVVMViewClass_SourceKey SourceKey, const FMVVMViewClass_Source& ClassSource, FMVVMView_Source& ViewSource);`
- L204 _private prototype_ `void UninitializeSource(FMVVMView_SourceKey SourceKey);`
- L205 _private prototype_ `bool SetSourceInternal(FMVVMViewClass_SourceKey SourceKey, TScriptInterface<INotifyFieldValueChanged> ViewModel, bool bForDynamicSource);`
- L207 _private prototype_ `void InitializeSourceParentBinding(FMVVMView_SourceKey SourceKey);`
- L208 _private prototype_ `void UninitializeSourceParentBinding(FMVVMView_SourceKey SourceKey);`
- L211 _private prototype_ `void InitializeSourceBindings(FMVVMView_SourceKey SourceKey, bool bRunAllBindings);`
- L212 _private prototype_ `void InitializeSourceBindingsCommon();`
- L213 _private prototype_ `void UninitializeSourceBindings(FMVVMViewClass_SourceKey SourceKey, const FMVVMViewClass_Source& ClassSource, FMVVMView_Source& ViewSource);`
- L214 _private prototype_ `void HandledLibraryBindingValueChanged(UObject* InSource, UE::FieldNotification::FFieldId InFieldId, FMVVMView_SourceKey SourceKey);`
- L215 _private prototype_ `void ExecuteBindingInternal(const FMVVMViewClass_SourceBinding& SourceBinding) const;`
- L216 _private prototype_ `void ExecuteBindingImmediately(const FMVVMViewClass_Binding& ClassBinding, FMVVMViewClass_BindingKey KeyForLog) const;`
- L217 _private prototype_ `void ExecuteViewModelBindingsInternal(FMVVMViewClass_SourceKey SourceKey);`
- L219 _private prototype_ `void ExecuteConditionInternal(const FMVVMViewClass_SourceCondition& SourceCondition) const;`
- L222 _private prototype_ `bool EvaluateSource(FMVVMViewClass_SourceKey SourceIndex);`
- L223 _private prototype_ `void HandleViewModelCollectionChanged();`
- L226 _private prototype_ `void BindEvent(const FMVVMViewClass_Event& ClassItem, FMVVMViewClass_EventKey KeyForLog);`
- L227 _private prototype_ `void UnbindEvent(int32 BoundEventIndex);`
- L228 _private prototype_ `void ReinitializeEvents(FMVVMViewClass_SourceKey SourceKey, UObject* PreviousValue, UObject* NewValue);`
- L230 _private prototype_ `void HandleBlueprintPreCompile(UBlueprint* Blueprint);`
- L235 _private member_ `TObjectPtr<const UMVVMViewClass> GeneratedViewClass;` — `UPROPERTY(Transient)`
- L238 _private member_ `TArray<FMVVMView_Source> Sources;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "View")`
- L247 _private member_ `TArray<FBoundEvent> BoundEvents;` — The event that are registered by the view to the sources.
- L249 _private member_ `TMap<TPair<int32 , int32 >, FDelegateHandle> RegisteredBindings;`
- L252 _private member_ `TArray<TObjectPtr<UMVVMViewExtension>> Extensions;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "View")`
- L256 _private member_ `uint64 ValidSources = 0;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "View")` — Bitfield that represents the valid sources.
- L260 _private member_ `uint8 NumberOfSourceWithTickBinding = 0;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "View")` — The number of source has at least one binding that need to be ticked every frame.
- L264 _private member_ `bool bLogBinding = false;` — `UPROPERTY(EditAnywhere, Transient, Category = "View")` — Should log when a binding is executed.
- L268 _private member_ `bool bConstructed = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "View")` — Is the Construct method called.
- L272 _private member_ `bool bSourcesInitialized = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "View")` — Is the Initialize method called.
- L276 _private member_ `bool bBindingsInitialized = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "View")` — Is the Initialize method called.
- L280 _private member_ `bool bEventsInitialized = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "View")` — Is the Initialize method called.
- L284 _private member_ `bool bHasDefaultTickBinding = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "View")` — Is the view is registered to the binding subsystem for tick.
- L287 _private member_ `FDelegateHandle BlueprintPreCompileHandle;`

#### struct `UMVVMView::FBoundEvent`  
`struct FBoundEvent`  
_L240-245_
- L242 _public member_ `FWeakObjectPtr Object;`
- L243 _public member_ `FName PropertyName;`
- L244 _public member_ `FMVVMViewClass_EventKey EventKey;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/View/MVVMViewClass.h` (Public)


#### struct `FMVVMViewClass_SourceBinding`  
`struct FMVVMViewClass_SourceBinding`  
_L30-73_
- reflection: `USTRUCT()`
- desc: A structure to identify the Binding and the associated FieldId
- L41 _public function_ `FFieldNotificationId GetFieldId() const` — The id for the FieldId on the source. Valid when it is OneWay or when we need to register to the FieldNotify system.
- L47 _public function_ `FMVVMViewClass_BindingKey GetBindingKey() const` — The key to identify a binding in the view class.
- L53 _public function_ `bool ExecuteAtInitialization() const` — @return true if this Binding should be executed at initialization.
- L60 _private member_ `FFieldNotificationId FieldId;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L63 _private member_ `FMVVMViewClass_BindingKey BindingKey;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L72 _private member_ `uint8 Flags = (uint8)EFlags::None;` — `UPROPERTY(VisibleAnywhere, Category = "View")`

#### enum `FMVVMViewClass_SourceBinding::EFlags`  
`enum class EFlags : uint8`  
_L65-69_
- L67 _public enumerator_ `None = 0`
- L68 _public enumerator_ `ExecuteAtInitialization = 1 << 0`

#### struct `FMVVMViewClass_SourceCondition`  
`struct FMVVMViewClass_SourceCondition`  
_L79-107_
- reflection: `USTRUCT()`
- desc: A structure to identify the Condition and the associated FieldId
- L90 _public function_ `FFieldNotificationId GetFieldId() const` — The id for the FieldId on the source. Valid when it is OneWay or when we need to register to the FieldNotify system.
- L96 _public function_ `FMVVMViewClass_ConditionKey GetConditionKey() const` — The key to identify a binding in the view class.
- L103 _private member_ `FFieldNotificationId FieldId;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L106 _private member_ `FMVVMViewClass_ConditionKey ConditionKey;` — `UPROPERTY(VisibleAnywhere, Category = "View")`

#### struct `FMVVMViewClass_Binding`  
`struct FMVVMViewClass_Binding`  
_L114-205_
- reflection: `USTRUCT()`
- desc: A compiled and shared binding for ViewModel<->View
- L122 _public function_ `const FMVVMVCompiledBinding& GetBinding() const` — @return the binding. From source to destination (if forward) or from destination to source (if backward).
- L128 _public function_ `bool IsShared() const` — @return true if multiple field or source can trigger this binding.
- L134 _public function_ `bool IsOneWay() const` — @return true if this Binding should be executed once (at initialization) and when FieldId is broadcasted.
- L144 _public function_ `uint64 GetSources() const` — A view binding may require more than one view sources to run the binding. A binding will not execute if any view source is invalid. It will not warn if the view source is make as optional.
- L150 _public prototype_ `EMVVMExecutionMode GetExecuteMode() const;` — How/when the binding should be executed.
- L154 _public function_ `FGuid GetEditorId() const` — Get the id of the BlueprintViewBinding.
- L174 _public prototype_ `FString ToString(const UMVVMViewClass* ViewClass, FToStringArgs Args) const;` — @return a human readable version of the source that can be use for debugging purposes.
- L188 _private member_ `FMVVMVCompiledBinding Binding;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L193 _private member_ `uint8 Flags = (uint8)EFlags::None;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L196 _private member_ `EMVVMExecutionMode ExecutionMode = EMVVMExecutionMode::Immediate;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L199 _private member_ `uint64 SourceBitField = 0;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L203 _private member_ `FGuid EditorId;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FMVVMViewClass_Binding::FToStringArgs`  
`struct FToStringArgs`  
_L161-171_
- L163 _public member_ `bool bUseDisplayName = true;`
- L164 _public member_ `bool bAddFlags = true;`
- L165 _public member_ `bool bAddBindingId = true;`
- L166 _public member_ `bool bAddBindingFields = true;`
- L167 _public member_ `bool bAddSources = true;`
- L169 _public prototype_ `static FToStringArgs Short();`
- L170 _public prototype_ `static FToStringArgs All();`

#### enum `FMVVMViewClass_Binding::EFlags`  
`enum class EFlags : uint8`  
_L178-185_
- L180 _public enumerator_ `None = 0`
- L181 _public enumerator_ `OneWay = 1 << 0`
- L182 _public enumerator_ `Shared = 1 << 1`
- L183 _public enumerator_ `OverrideExecuteMode = 1 << 2`
- L184 _public enumerator_ `EnabledByDefault = 1 << 3`

#### struct `FMVVMViewClass_EvaluateSource`  
`struct FMVVMViewClass_EvaluateSource`  
_L212-259_
- reflection: `USTRUCT()`
- desc: A binding to evaluate the source when something change in its path.
- L220 _public function_ `FFieldNotificationId GetFieldId() const` — The id for the FieldId on the source on the parent that will trigger the evaluation.
- L226 _public function_ `FMVVMViewClass_SourceKey GetParentSource() const` — The source that owns the source.
- L232 _public function_ `FMVVMViewClass_SourceKey GetSource() const` — The source that needs to be evaluated.
- L247 _public prototype_ `FString ToString(const UMVVMViewClass* ViewClass, FToStringArgs Args) const;` — @return a human readable version of the source that can be use for debugging purposes.
- L252 _private member_ `FFieldNotificationId ParentFieldId;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L255 _private member_ `FMVVMViewClass_SourceKey ParentSource;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L258 _private member_ `FMVVMViewClass_SourceKey ToEvaluate;` — `UPROPERTY(VisibleAnywhere, Category = "View")`

#### struct `FMVVMViewClass_EvaluateSource::FToStringArgs`  
`struct FToStringArgs`  
_L238-244_
- L240 _public member_ `bool bUseDisplayName = true;`
- L242 _public prototype_ `static FToStringArgs Short();`
- L243 _public prototype_ `static FToStringArgs All();`

#### struct `FMVVMViewClass_Source`  
`struct FMVVMViewClass_Source`  
_L266-493_
- reflection: `USTRUCT()`
- desc: Shared data to find or create a ViewModel at runtime.
- L274 _public prototype_ `UObject* GetOrCreateInstance(const UMVVMViewClass* ViewClass, UMVVMView* View, UUserWidget* UserWidget) const;` — Get or create the instance used to register the bindings.
- L277 _public prototype_ `void ReleaseInstance(UObject* ViewModel, const UMVVMView* View) const;` — The source is not needed anymore.
- L280 _public prototype_ `TScriptInterface<INotifyFieldValueChanged> GetGlobalCollectionViewModel(UUserWidget* UserWidget) const;` — Returns the viewmodel inside the global viewmodel collection.
- L297 _public prototype_ `FParentSourceInfo GetParentSupplyingSourceClass(UUserWidget* UserWidget) const;` — Get the parent vm view that has a matching vm class source
- L300 _public function_ `UClass* GetSourceClass() const` — The expected class of the source.
- L306 _public function_ `bool IsUserWidget() const` — The source is the UserWidget.
- L312 _public function_ `bool IsViewModel() const` — The source is a viewmodel added in the editor.
- L321 _public function_ `bool IsUserWidgetProperty() const` — The source is UserWidget's property. @return false if the source is from a long path or the source is the UserWidget.
- L327 _public function_ `bool RequireSettingUserWidgetProperty() const` — The UserWidget's property need to be set/reset when the Source is created/release.
- L333 _public function_ `bool CanBeSet() const` — Can be set at runtime from SetViewModel.
- L339 _public function_ `bool CanBeEvaluated() const` — The source "GetOrCreateInstance" can be reevaluated.
- L345 _public function_ `bool HasEvaluateBindings() const` — The source has at least one evaluate binding.
- L351 _public function_ `bool RequireGlobalViewModelCollectionUpdate() const` — The source has at least one evaluate binding.
- L357 _public function_ `bool AlwaysExecuteBindingsOnSetSource() const` — When a source is manually set, then always execute that source the bindings.
- L363 _public function_ `bool IsParentContextReference() const` — If we're going to lookup the vm from a parent view
- L372 _public function_ `bool IsOptional() const` — The source GetOrCreateInstance can fail. The view will not warn if a binding can't execute because the source is invalid.
- L378 _public function_ `bool HasTickBindings() const` — The source has at least one binding that need to be tick every frame.
- L384 _public function_ `FName GetName() const` — The name of the source.
- L390 _public function_ `FName GetUserWidgetPropertyName() const` — The name of the UserWidget's property.
- L399 _public function_ `const TArrayView<const FMVVMViewClass_FieldId> GetFieldIds() const` — FieldId owns by the source that we need to register to. Only contains id for OneWay bindings or Evaluate bindings.
- L405 _public function_ `const TArrayView<const FMVVMViewClass_SourceBinding> GetBindings() const` — The list of bindings owns by the source. A binding can be owns by more than one source.
- L410 _public function_ `const TArrayView<const FMVVMViewClass_SourceCondition> GetConditions() const`
- L430 _public prototype_ `FString ToString(const UMVVMViewClass* ViewClass, FToStringArgs Args) const;` — @return a human readable version of the source that can be use for debugging purposes.
- L436 _private member_ `TSubclassOf<UObject> ExpectedSourceType;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — Class type to create a source at runtime.
- L440 _private member_ `TObjectPtr<UMVVMViewModelContextResolver> Resolver = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "View", Instanced)` — The resolver to fetch the source at runtime.
- L444 _private member_ `FMVVMViewModelContext GlobalViewModelInstance;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — Info to find the ViewModel instance at runtime.
- L452 _private member_ `FMVVMVCompiledFieldPath FieldPath;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — A resolvable path to retrieve the source instance at runtime. It can be a path "Property = Object.Function.Object". It can be a UFunction's name of a FProperty's name.
- L455 _private member_ `FName PropertyName;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L459 _private member_ `TArray<FMVVMViewClass_FieldId> FieldToRegisterTo;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — All the fields that the view need to register to for this source.
- L466 _private member_ `TArray<FMVVMViewClass_SourceBinding> Bindings;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — All the bindings this source need to execute at initialization (OneTime) And the bindings that needs to execute when the FieldId matches (OneWay).
- L470 _private member_ `TArray<FMVVMViewClass_SourceCondition> Conditions;` — `UPROPERTY(VisibleAnywhere, Category = "View")` — All the conditions that need to execute when Field value changes
- L492 _private member_ `uint16 Flags = (uint16)EFlags::None;` — `UPROPERTY(VisibleAnywhere, Category = "View")`

#### struct `FMVVMViewClass_Source::FParentSourceInfo`  
`struct FParentSourceInfo`  
_L283-294_
- desc: Helper struct to provide info about where context data is coming from
- L286 _public member_ `const UMVVMView* ParentView = nullptr;` — Parent view info will only be set if a parent widget was found that has the same class/name in it's view
- L287 _public member_ `FMVVMView_SourceKey ParentSourceKey;`
- L290 _public member_ `UUserWidget* ParentUserWidget = nullptr;` — Parent User Widget will always be valid if Source is valid or if the ParentView is valid
- L293 _public member_ `UObject* Source = nullptr;` — May be valid or not if the parent view is found, otherwise will only be valid if and external source was provided

#### struct `FMVVMViewClass_Source::FToStringArgs`  
`struct FToStringArgs`  
_L416-427_
- L418 _public member_ `FMVVMViewClass_Binding::FToStringArgs Bindings;`
- L419 _public member_ `bool bUseDisplayName = true;`
- L420 _public member_ `bool bAddCreationMode = true;`
- L421 _public member_ `bool bAddFields = true;`
- L422 _public member_ `bool bAddBindings = true;`
- L423 _public member_ `bool bAddFlags = true;`
- L425 _public prototype_ `static FToStringArgs Short();`
- L426 _public prototype_ `static FToStringArgs All();`

#### enum `FMVVMViewClass_Source::EFlags`  
`enum class EFlags : uint16`  
_L472-489_
- L474 _public enumerator_ `None = 0`
- L475 _public enumerator_ `TypeCreateInstance = 1 << 0`
- L476 _public enumerator_ `IsUserWidgetProperty = 1 << 1`
- L477 _public enumerator_ `SetUserWidgetProperty = 1 << 2`
- L478 _public enumerator_ `IsOptional = 1 << 3`
- L479 _public enumerator_ `CanBeSet = 1 << 4`
- L480 _public enumerator_ `CanBeEvaluated = 1 << 5`
- L481 _public enumerator_ `HasEvaluatedBindings = 1 << 6`
- L482 _public enumerator_ `SelfReference = 1 << 7`
- L483 _public enumerator_ `HasTickBindings = 1 << 8`
- L484 _public enumerator_ `IsViewModel = 1 << 9`
- L485 _public enumerator_ `IsViewModelInstanceExposed = 1 << 10`
- L486 _public enumerator_ `GlobalViewModelCollectionUpdate = 1 << 11`
- L487 _public enumerator_ `AlwaysExecuteBindingsOnSetSource = 1 << 12`
- L488 _public enumerator_ `ParentContextReference = 1 << 13`

#### struct `FMVVMViewClass_Event`  
`struct FMVVMViewClass_Event`  
_L500-565_
- reflection: `USTRUCT()`
- desc: A compiled and shared delegate bindings
- L511 _public function_ `const FMVVMVCompiledFieldPath& GetMulticastDelegatePath() const` — The path to get access to the multicast from the UserWidget. Include the name of the Widget/ViewModel
- L517 _public function_ `const FName GetUserWidgetFunctionName() const` — The name of the UFunction on the UserWidget.
- L526 _public function_ `FMVVMViewClass_SourceKey GetSourceKey() const` — The source, if the multicast parent is a valid source. This is used when the source value changes at runtime and we want to bound the event again.
- L536 _public function_ `uint64 GetSources() const` — A view event may require more than one view sources to run the event. A event will not execute if any view source is invalid. It will not warn if the view source is make as optional.
- L550 _public prototype_ `FString ToString(const UMVVMViewClass* ViewClass, FToStringArgs Args) const;` — @return a human readable version of the binding that can be use for debugging purposes.
- L555 _private member_ `FMVVMVCompiledFieldPath FieldPath;` — `UPROPERTY()`
- L558 _private member_ `FName UserWidgetFunctionName;` — `UPROPERTY()`
- L561 _private member_ `FMVVMViewClass_SourceKey SourceToReevaluate;` — `UPROPERTY()`
- L564 _private member_ `uint64 SourceBitField = 0;` — `UPROPERTY()`

#### struct `FMVVMViewClass_Event::FToStringArgs`  
`struct FToStringArgs`  
_L542-548_
- L544 _public member_ `bool bUseDisplayName = true;`
- L546 _public prototype_ `static FToStringArgs Short();`
- L547 _public prototype_ `static FToStringArgs All();`

#### struct `FMVVMViewClass_Condition`  
`struct FMVVMViewClass_Condition`  
_L568-622_
- reflection: `USTRUCT()`
- L577 _public function_ `const FName GetUserWidgetFunctionName() const` — The name of the UFunction on the UserWidget.
- L586 _public function_ `FMVVMViewClass_SourceKey GetSourceKey() const` — The source, if the multicast parent is a valid source. This is used when the source value changes at runtime and we want to bound the event again.
- L596 _public function_ `uint64 GetSources() const` — A view event may require more than one view sources to run the event. A event will not execute if any view source is invalid. It will not warn if the view source is make as optional.
- L610 _public prototype_ `FString ToString(const UMVVMViewClass* ViewClass, FToStringArgs Args) const;` — @return a human readable version of the binding that can be use for debugging purposes.
- L615 _private member_ `FName UserWidgetFunctionName;` — `UPROPERTY()`
- L618 _private member_ `FMVVMViewClass_SourceKey SourceToReevaluate;` — `UPROPERTY()`
- L621 _private member_ `uint64 SourceBitField = 0;` — `UPROPERTY()`

#### struct `FMVVMViewClass_Condition::FToStringArgs`  
`struct FToStringArgs`  
_L602-608_
- L604 _public member_ `bool bUseDisplayName = true;`
- L606 _public prototype_ `static FToStringArgs Short();`
- L607 _public prototype_ `static FToStringArgs All();`

#### class `UMVVMViewClass`  
`class UMVVMViewClass : public UWidgetBlueprintGeneratedClassExtension`  
_L628-826_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidgetBlueprintGeneratedClassExtension`
- desc: Shared between every instances of the same View class.
- L636 _public prototype_ `virtual void Initialize(UUserWidget* UserWidget) override;`
- L637 _public prototype_ `virtual void Construct(UUserWidget* UserWidget) override;`
- L638 _public prototype_ `virtual void Destruct(UUserWidget* UserWidget) override;`
- L640 _public prototype_ `virtual void BeginDestroy() override;`
- L646 _public function_ `[[nodiscard]] bool DoesInitializeSourcesOnConstruct() const` — Should it automatically create the binding sources when the view is constructed.
- L652 _public function_ `[[nodiscard]] bool DoesInitializeBindingsOnConstruct() const` — Should it automatically register and execute the bindings when the view is constructed.
- L658 _public function_ `[[nodiscard]] bool DoesInitializeEventsOnConstruct() const` — Should it automatically register the events when the view is constructed.
- L664 _public function_ `[[nodiscard]] bool DoesListenToViewModelCollectionChanged() const` — Should the view listen to modification made in the global viewmodel collection.
- L670 _public function_ `[[nodiscard]] bool IsCreatedWithoutBindings() const` — Should the view be created even when there are no bindings or events.
- L676 _public function_ `[[nodiscard]] const FMVVMCompiledBindingLibrary& GetBindingLibrary() const` — Get the container of all the bindings.
- L685 _public function_ `uint64 GetOptionalSources() const` — The field of all the sources that are optional.
- L691 _public function_ `[[nodiscard]] const TArrayView<const FMVVMViewClass_Source> GetSources() const` — Get the list of all the needed viewmodel or widgets.
- L697 _public function_ `[[nodiscard]] const FMVVMViewClass_Source& GetSource(FMVVMViewClass_SourceKey Key) const` — The shared source used by the view.
- L704 _public function_ `[[nodiscard]] const TArrayView<const FMVVMViewClass_Binding> GetBindings() const` — The list of bindings. A binding can be used by more than one source.
- L710 _public function_ `[[nodiscard]] const FMVVMViewClass_Binding& GetBinding(FMVVMViewClass_BindingKey Key) const` — The binding (can be shared by more than one source).
- L717 _public function_ `[[nodiscard]] const TArrayView<const FMVVMViewClass_EvaluateSource> GetEvaluateSources() const` — The list of evaluate bindings.
- L723 _public function_ `[[nodiscard]] const FMVVMViewClass_EvaluateSource& GetEvaluateSource(FMVVMViewClass_EvaluateBindingKey Key) const` — The evaluate binding.
- L730 _public function_ `[[nodiscard]] const TArrayView<const FMVVMViewClass_Event> GetEvents() const` — The list of events.
- L736 _public function_ `[[nodiscard]] const FMVVMViewClass_Event& GetEvent(FMVVMViewClass_EventKey Key) const` — The event.
- L743 _public function_ `[[nodiscard]] const TArrayView<const FMVVMViewClass_Condition> GetConditions() const` — The list of conditions.
- L749 _public function_ `[[nodiscard]] const FMVVMViewClass_Condition& GetCondition(FMVVMViewClass_ConditionKey Key) const` — The condition.
- L756 _public function_ `[[nodiscard]] const TArrayView<const TObjectPtr<UMVVMViewClassExtension>> GetViewClassExtensions() const` — The list of extensions for widgets.
- L772 _public prototype_ `[[nodiscard]] FString ToString(FToStringArgs SourceArgs) const;`
- L777 _private prototype_ `void HandleBlueprintCompiled();`
- L778 _private prototype_ `void ReloadIfDirty() const;`
- L779 _private member_ `std::atomic<bool> BindingLibraryDirty = false;`
- L784 _private member_ `TArray<FMVVMViewClass_Source> Sources;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L786 _private member_ `TArray<FMVVMViewClass_Binding> Bindings;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L788 _private member_ `TArray<FMVVMViewClass_EvaluateSource> EvaluateSources;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L790 _private member_ `TArray<FMVVMViewClass_Event> Events;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L792 _private member_ `TArray<FMVVMViewClass_Condition> Conditions;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L796 _private member_ `TArray<TObjectPtr<UMVVMViewClassExtension>> ViewClassExtensions;` — `UPROPERTY(Instanced)` — All MVVM extensions on widgets of the owning userwidget.
- L800 _private member_ `FMVVMCompiledBindingLibrary BindingLibrary;` — `UPROPERTY()` — All the bindings shared between all the View instance.
- L804 _private member_ `uint64 OptionalSources;` — `UPROPERTY()` — Which view source are optional.
- L806 _private member_ `int32 ViewCounter = 0;`
- L809 _private member_ `bool bInitializeSourcesOnConstruct = true;` — `UPROPERTY()`
- L812 _private member_ `bool bInitializeBindingsOnConstruct = true;` — `UPROPERTY()`
- L815 _private member_ `bool bInitializeEventsOnConstruct = true;` — `UPROPERTY()`
- L818 _private member_ `bool bListenToViewModelCollectionChanged = false;` — `UPROPERTY()`
- L821 _private member_ `bool bCreateViewWithoutBindings = false;` — `UPROPERTY()`
- L824 _private member_ `FDelegateHandle BlueprintCompiledHandle;`

#### struct `UMVVMViewClass::FToStringArgs`  
`struct FToStringArgs`  
_L762-771_
- L764 _public member_ `FMVVMViewClass_Source::FToStringArgs Source;`
- L765 _public member_ `FMVVMViewClass_Binding::FToStringArgs Binding;`
- L766 _public member_ `FMVVMViewClass_EvaluateSource::FToStringArgs Evaluate;`
- L767 _public member_ `FMVVMViewClass_Event::FToStringArgs Event;`
- L769 _public prototype_ `static FToStringArgs Short();`
- L770 _public prototype_ `static FToStringArgs All();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MVVM` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/View/MVVMViewDeprecatedTypes.h` (Public)


#### struct `FMVVMVCompiledFieldId`  
`FMVVMVCompiledFieldId`  
_L22-41_
- reflection: `UE_DEPRECATED(5.4, "FMVVMVCompiledFieldId is no longer used.")`
- L26 _public function_ `bool IsValid() const`
- L32 _private typedef_ `using IndexType = int16;`
- L35 _private member_ `int16 FieldIdIndex = INDEX_NONE;` — `UPROPERTY()`
- L39 _private member_ `FGuid CompiledBindingLibraryId;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FMVVMViewSource`  
`FMVVMViewSource`  
_L46-75_
- reflection: `UE_DEPRECATED(5.4, "FMVVMViewSource is no longer used, please use FMVVMView_Source instead.")`
- L51 _public member_ `TObjectPtr<UObject> Source;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — TScriptInterface<INotifyFieldValueChanged>
- L54 _public member_ `FName SourceName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L58 _public member_ `int32 RegisteredCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — Number of bindings connected to the source.
- L62 _public member_ `bool bCreatedSource = false;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — The source is defined in the ClassExtension.
- L66 _public member_ `bool bBindingsInitialized = false;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — The source bindings are initialized
- L70 _public member_ `bool bSetManually = false;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — The source was set manually via SetViewModel.
- L74 _public member_ `bool bAssignedToUserWidgetProperty = false;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — The source was set to a UserWidget property.

#### struct `FMVVMViewClass_SourceCreator`  
`FMVVMViewClass_SourceCreator`  
_L80-169_
- reflection: `UE_DEPRECATED(5.4, "FMVVMViewClass_SourceCreator is no longer used, please use FMVVMViewClass_Source instead.")`
- L85 _public function_ `UObject* CreateInstance(const UMVVMViewClass* ViewClass, UMVVMView* View, UUserWidget* UserWidget) const`
- L90 _public function_ `void DestroyInstance(const UObject* ViewModel, const UMVVMView* View) const`
- L94 _public function_ `UClass* GetSourceClass() const`
- L99 _public function_ `bool IsSourceAUserWidgetProperty() const`
- L104 _public function_ `bool CanBeSet() const`
- L109 _public function_ `bool CanBeEvaluated() const`
- L114 _public function_ `bool IsOptional() const`
- L119 _public function_ `FName GetSourceName() const`
- L124 _public function_ `FName GetParentSourceName() const`
- L139 _public function_ `FString ToString(const FMVVMCompiledBindingLibrary& CompiledBindingLibrary, FToStringArgs Args) const`
- L144 _private member_ `TSubclassOf<UObject> ExpectedSourceType;` — `UPROPERTY()`
- L146 _private member_ `TObjectPtr<UMVVMViewModelContextResolver> Resolver = nullptr;` — `UPROPERTY(Instanced)`
- L148 _private member_ `FMVVMViewModelContext GlobalViewModelInstance;` — `UPROPERTY()`
- L150 _private member_ `FMVVMVCompiledFieldPath FieldPath;` — `UPROPERTY()`
- L152 _private member_ `FName PropertyName;` — `UPROPERTY()`
- L154 _private member_ `FName ParentSourceName;` — `UPROPERTY()`
- L168 _private member_ `uint8 Flags = (uint8)ESourceFlags::None;` — `UPROPERTY()`

#### struct `FMVVMViewClass_SourceCreator::FToStringArgs`  
`struct FToStringArgs`  
_L130-138_
- L132 _public member_ `bool bUseDisplayName = true;`
- L133 _public member_ `bool bAddCreationMode = true;`
- L134 _public member_ `bool bAddFlags = true;`
- L136 _public function_ `static FToStringArgs Short()`
- L137 _public function_ `static FToStringArgs All()`

#### enum `FMVVMViewClass_SourceCreator::ESourceFlags`  
`enum class ESourceFlags : uint8`  
_L156-165_
- L158 _public enumerator_ `None = 0`
- L159 _public enumerator_ `TypeCreateInstance = 1 << 0`
- L160 _public enumerator_ `IsUserWidgetProperty = 1 << 1`
- L161 _public enumerator_ `IsOptional = 1 << 2`
- L162 _public enumerator_ `CanBeSet = 1 << 3`
- L163 _public enumerator_ `CanBeEvaluated = 1 << 4`
- L164 _public enumerator_ `SelfReference = 1 << 5`

#### struct `FMVVMViewClass_CompiledBinding`  
`FMVVMViewClass_CompiledBinding`  
_L175-309_
- reflection: `UE_DEPRECATED(5.4, "FMVVMViewClass_CompiledBinding is no longer used, please use FMVVMViewClass_Binding and FMVVMViewClass_SourceBinding instead.")`
- L180 _public function_ `FMVVMVCompiledFieldId GetSourceFieldId() const`
- L185 _public function_ `FName GetSourceName() const`
- L190 _public function_ `int32 GetEvaluateSourceCreatorBindingIndex() const`
- L195 _public function_ `bool IsSourceUserWidget() const`
- L200 _public function_ `const FMVVMVCompiledBinding& GetBinding() const`
- L205 _public function_ `bool NeedsExecutionAtInitialization() const`
- L210 _public function_ `bool IsOneTime() const`
- L215 _public function_ `bool IsEnabledByDefault() const`
- L220 _public function_ `bool IsRegistrationOptional() const`
- L225 _public function_ `bool IsEvaluateSourceCreatorBinding() const`
- L230 _public function_ `bool IsConversionFunctionComplex() const`
- L235 _public function_ `EMVVMExecutionMode GetExecuteMode() const`
- L260 _public function_ `FString ToString() const`
- L264 _public function_ `FString ToString(const FMVVMCompiledBindingLibrary& CompiledBindingLibrary, FToStringArgs Args) const`
- L271 _public function_ `FGuid GetEditorId() const`
- L279 _private member_ `FMVVMVCompiledFieldId FieldId;` — `UPROPERTY()`
- L281 _private member_ `FName SourcePropertyName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L283 _private member_ `FMVVMVCompiledBinding Binding;` — `UPROPERTY()`
- L285 _private member_ `EMVVMExecutionMode ExecutionMode = EMVVMExecutionMode::Immediate;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L287 _private member_ `int8 EvaluateSourceCreatorIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L303 _private member_ `uint8 Flags = EBindingFlags::None;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L307 _private member_ `FGuid EditorId;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FMVVMViewClass_CompiledBinding::FToStringArgs`  
`struct FToStringArgs`  
_L241-257_
- L243 _public member_ `bool bUseDisplayName = true;`
- L244 _public member_ `bool bAddFieldPath = true;`
- L245 _public member_ `bool bAddFieldId = true;`
- L246 _public member_ `bool bAddFlags = true;`
- L247 _public member_ `bool bAddBindingId = true;`
- L249 _public function_ `static FToStringArgs Short()`
- L253 _public function_ `static FToStringArgs All()`

#### enum `FMVVMViewClass_CompiledBinding::EBindingFlags`  
`enum EBindingFlags`  
_L289-300_
- L291 _public enumerator_ `None = 0`
- L292 _public enumerator_ `ExecuteAtInitialization = 1 << 0`
- L293 _public enumerator_ `Unused01 = 1 << 1`
- L294 _public enumerator_ `OneTime = 1 << 2`
- L295 _public enumerator_ `EnabledByDefault = 1 << 3`
- L296 _public enumerator_ `ViewModelOptional = 1 << 4`
- L297 _public enumerator_ `Unused02 = 1 << 5`
- L298 _public enumerator_ `OverrideExecuteMode = 1 << 6`
- L299 _public enumerator_ `SourceObjectIsSelf = 1 << 7`

#### struct `FMVVMViewClass_CompiledEvent`  
`FMVVMViewClass_CompiledEvent`  
_L316-354_
- reflection: `UE_DEPRECATED(5.4, "MVVMViewClass_CompiledEvent is no longer used, please use MVVMViewClass_Event instead.")`
- L321 _public function_ `FName GetSourceName() const`
- L326 _public function_ `const FMVVMVCompiledFieldPath& GetMulticastDelegatePath() const`
- L331 _public function_ `const FName GetUserWidgetFunctionName() const`
- L341 _public function_ `FString ToString(const FMVVMCompiledBindingLibrary& CompiledBindingLibrary, FToStringArgs Args) const`
- L349 _private member_ `FMVVMVCompiledFieldPath FieldPath;` — `UPROPERTY()`
- L351 _private member_ `FName FunctionName;` — `UPROPERTY()`
- L353 _private member_ `FName SourceName;` — `UPROPERTY()`

#### struct `FMVVMViewClass_CompiledEvent::FToStringArgs`  
`struct FToStringArgs`  
_L337-340_
- L339 _public member_ `bool bUseDisplayName = true;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/View/MVVMViewModelContextResolver.h` (Public)


#### class `UMVVMViewModelContextResolver`  
`class UMVVMViewModelContextResolver : public UObject`  
_L20-56_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, EditInlineNew, DisplayName = "Viewmodel Resolver")`
- inherits: `UObject`
- desc: Shared data to find or create a ViewModel at runtime.
- L25 _public function_ `virtual UObject* CreateInstance(const UClass* ExpectedType, const UUserWidget* UserWidget, const UMVVMView* View) const`
- L31 _public prototype_ `TScriptInterface<INotifyFieldValueChanged> K2_CreateInstance(const UClass* ExpectedType, const UUserWidget* UserWidget) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Viewmodel", meta = (DisplayName = "Create Instance"))`
- L33 _public function_ `virtual void DestroyInstance(UObject* ViewModel, const UMVVMView* View) const`
- L39 _public prototype_ `void K2_DestroyInstance(UObject* ViewModel, const UMVVMView* View) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Viewmodel", meta = (DisplayName = "Destroy Instance"))`
- L43 _public prototype_ `virtual bool DoesSupportViewModelClass(const UClass* Class) const;`
- L50 _private member_ `TArray<FSoftClassPath> AllowedViewModelClasses;` — `UPROPERTY(EditDefaultsOnly, Category = "Viewmodel", meta=(MustImplement="/Script/FieldNotification.NotifyFieldValueChanged", DisallowedClasses="/Script/UMG.Widget"))` — Viewmodel class that the resolver supports.
- L54 _private member_ `TArray<FSoftClassPath> DeniedViewModelClasses;` — `UPROPERTY(EditDefaultsOnly, Category = "Viewmodel", meta=(MustImplement="/Script/FieldNotification.NotifyFieldValueChanged", DisallowedClasses="/Script/UMG.Widget"))` — Viewmodel class that the resolver explicitly does not support.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/View/MVVMViewTypes.h` (Public)


#### struct `FMVVMViewClass_FieldId`  
`struct FMVVMViewClass_FieldId`  
_L18-58_
- reflection: `USTRUCT()`
- desc: FieldName and Bit needed to create a UE::FieldNotification::FFieldId.
- L26 _public prototype_ `FMVVMViewClass_FieldId() = default;`
- L27 _public function_ `explicit FMVVMViewClass_FieldId(UE::FieldNotification::FFieldId InFieldId)`
- L33 _public function_ `bool IsValid() const`
- L38 _public function_ `UE::FieldNotification::FFieldId GetFieldId() const`
- L43 _public function_ `FName GetName() const`
- L48 _public function_ `bool operator== (const FMVVMViewClass_FieldId& Other) const`
- L55 _private member_ `FName FieldName;` — `UPROPERTY(VisibleAnywhere, Category = "View")`
- L57 _private member_ `int32 FieldIndex = INDEX_NONE;`

#### struct `FMVVMViewClass_SourceKey`  
`struct FMVVMViewClass_SourceKey`  
_L64-98_
- reflection: `USTRUCT()`
- desc: Key that identify the FMVVMViewClass_Source.
- L69 _public prototype_ `FMVVMViewClass_SourceKey() = default;`
- L70 _public function_ `FMVVMViewClass_SourceKey(int32 InIndex) : Index(InIndex)`
- L74 _public function_ `bool IsValid() const`
- L79 _public function_ `uint64 GetBit() const`
- L85 _public function_ `int32 GetIndex() const`
- L90 _public function_ `bool operator== (const FMVVMViewClass_SourceKey& Other) const`
- L97 _private member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "View")`

#### struct `FMVVMViewClass_BindingKey`  
`struct FMVVMViewClass_BindingKey`  
_L104-131_
- reflection: `USTRUCT()`
- desc: Key that identify the FMVVMViewClass_Binding.
- L109 _public prototype_ `FMVVMViewClass_BindingKey() = default;`
- L110 _public function_ `explicit FMVVMViewClass_BindingKey(int32 InIndex) : Index(InIndex)`
- L113 _public function_ `bool IsValid() const`
- L118 _public function_ `int32 GetIndex() const`
- L123 _public function_ `bool operator== (const FMVVMViewClass_BindingKey& Other) const`
- L130 _private member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "View")`

#### struct `FMVVMViewClass_EvaluateBindingKey`  
`struct FMVVMViewClass_EvaluateBindingKey`  
_L137-166_
- reflection: `USTRUCT()`
- desc: Key that identify the FMVVMViewClass_EvaluateBinding.
- L144 _public prototype_ `FMVVMViewClass_EvaluateBindingKey() = default;`
- L145 _public function_ `explicit FMVVMViewClass_EvaluateBindingKey(int32 InIndex) : Index(InIndex)`
- L148 _public function_ `bool IsValid() const`
- L153 _public function_ `int32 GetIndex() const`
- L158 _public function_ `bool operator== (const FMVVMViewClass_EvaluateBindingKey& Other) const`
- L165 _private member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "View")`

#### struct `FMVVMViewClass_EventKey`  
`struct FMVVMViewClass_EventKey`  
_L172-201_
- reflection: `USTRUCT()`
- desc: Key that identify the FMVVMViewClass_Event.
- L179 _public prototype_ `FMVVMViewClass_EventKey() = default;`
- L180 _public function_ `explicit FMVVMViewClass_EventKey(int32 InIndex) : Index(InIndex)`
- L183 _public function_ `bool IsValid() const`
- L188 _public function_ `int32 GetIndex() const`
- L193 _public function_ `bool operator== (const FMVVMViewClass_EventKey& Other) const`
- L200 _private member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "View")`

#### struct `FMVVMViewClass_ConditionKey`  
`struct FMVVMViewClass_ConditionKey`  
_L207-236_
- reflection: `USTRUCT()`
- desc: Key that identify the FMVVMViewClass_Condition.
- L214 _public prototype_ `FMVVMViewClass_ConditionKey() = default;`
- L215 _public function_ `explicit FMVVMViewClass_ConditionKey(int32 InIndex) : Index(InIndex)`
- L218 _public function_ `bool IsValid() const`
- L223 _public function_ `int32 GetIndex() const`
- L228 _public function_ `bool operator== (const FMVVMViewClass_ConditionKey& Other) const`
- L235 _private member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "View")`

#### struct `FMVVMView_SourceKey`  
`struct FMVVMView_SourceKey`  
_L243-271_
- reflection: `USTRUCT()`
- desc: Key that identify the FMVVMView_Source.
- L248 _public prototype_ `FMVVMView_SourceKey() = default;`
- L249 _public function_ `FMVVMView_SourceKey(int32 InIndex) : Index(InIndex)`
- L253 _public function_ `bool IsValid() const`
- L258 _public function_ `int32 GetIndex() const`
- L263 _public function_ `bool operator== (const FMVVMView_SourceKey& Other) const`
- L270 _private member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "View")`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MVVM` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/ViewModel/MVVMFieldNotificationDelegates.h` (Public)


#### class `UE::MVVM::FMVVMFieldNotificationDelegates`  
`class FMVVMFieldNotificationDelegates`  
_L16-31_
- desc: Basic implementation of the INotifyFieldValueChanged implementation.
- L19 _public prototype_ `FDelegateHandle AddFieldValueChangedDelegate(UObject* Owner, UE::FieldNotification::FFieldId InFieldId, INotifyFieldValueChanged::FFieldValueChangedDelegate InNewDelegate);`
- L20 _public prototype_ `void AddFieldValueChangedDelegate(UObject* Owner, UE::FieldNotification::FFieldId FieldId, const FFieldValueChangedDynamicDelegate& Delegate);`
- L21 _public prototype_ `bool RemoveFieldValueChangedDelegate(UObject* Owner, UE::FieldNotification::FFieldId InFieldId, FDelegateHandle InHandle);`
- L22 _public prototype_ `bool RemoveFieldValueChangedDelegate(UObject* Owner, UE::FieldNotification::FFieldId FieldId, const FFieldValueChangedDynamicDelegate& Delegate);`
- L23 _public prototype_ `int32 RemoveAllFieldValueChangedDelegates(UObject* Owner, FDelegateUserObjectConst InUserObject);`
- L24 _public prototype_ `int32 RemoveAllFieldValueChangedDelegates(UObject* Owner, UE::FieldNotification::FFieldId InFieldId, FDelegateUserObjectConst InUserObject);`
- L25 _public prototype_ `void BroadcastFieldValueChanged(UObject* Owner, UE::FieldNotification::FFieldId InFieldId);`
- L26 _public prototype_ `TArray<UE::FieldNotification::FFieldMulticastDelegate::FDelegateView> GetView() const;`
- L29 _private member_ `UE::FieldNotification::FFieldMulticastDelegate Delegates;`
- L30 _private member_ `TBitArray<> EnabledFieldNotifications;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FieldNotification` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/ViewModel/MVVMInstancedViewModelGeneratedClass.h` (Public)


#### class `UMVVMInstancedViewModelGeneratedClass`  
`class UMVVMInstancedViewModelGeneratedClass : public UBlueprintGeneratedClass`  
_L16-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintGeneratedClass`
- L21 _public prototype_ `virtual void Link(FArchive& Ar, bool bRelinkExistingProperties) override;`
- L24 _public prototype_ `virtual UClass* GetAuthoritativeClass() override;`
- L25 _public prototype_ `virtual void PurgeClass(bool bRecompilingOnLoad) override;`
- L26 _public prototype_ `void AddNativeRepNotifyFunction(UFunction* Function, const FProperty* Property);`
- L27 _public prototype_ `void PurgeNativeRepNotifyFunctions();`
- L33 _public prototype_ `void BroadcastFieldValueChanged(UObject* Object, const FProperty* Property);`
- L34 _public prototype_ `virtual void OnPropertyReplicated(UObject* Object, const FProperty* Property);`
- L38 _private member_ `TArray<TObjectPtr<UFunction>> OnRepFunctionToLink;` — `UPROPERTY()`
- L40 _private member_ `TMap<TObjectKey<UFunction>, const FProperty*> OnRepToPropertyMap;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELVIEWVIEWMODEL_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModel/Public/ViewModel/MVVMViewModelBlueprintGeneratedClass.h` (Public)


#### class `UDEPRECATED_MVVMViewModelBlueprintGeneratedClass`  
`class UE_DEPRECATED(5.5, "Use the regular BlueprintGeneratedClass.") UDEPRECATED_MVVMViewModelBlueprintGeneratedClass : public UBlueprintGeneratedClass`  
_L11-14_
- reflection: `UCLASS(Deprecated, MinimalAPI)`
- inherits: `UBlueprintGeneratedClass`
