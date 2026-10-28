# Plugins / MVVMToolset

- module root: `Plugins/Experimental/Toolsets/MVVMToolset/Source/MVVMToolset`
- headers: 1; symbols: 13
- symbol kinds: class=1, member=2, prototype=9, struct=1
- PrivateDependencyModuleNames: AssetRegistry, BlueprintEditorLibrary, BlueprintGraph, CoreUObject, Engine, Json, Kismet, ModelViewViewModel, ModelViewViewModelBlueprint, ModelViewViewModelEditor, ToolsetRegistry, UMG, UMGEditor, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/MVVMToolset/Source/MVVMToolset/Private/MVVMToolset/MVVMToolset.h` (Private)


#### struct `FMVVMViewConversionFunctionDescription`  
`struct FMVVMViewConversionFunctionDescription`  
_L15-26_
- reflection: `USTRUCT(BlueprintType)`
- desc: Information about a conversion function
- L21 _public member_ `TObjectPtr<const UFunction> ConversionFunction;` — `UPROPERTY(BlueprintReadOnly, Category = "MVVM")` — If the conversion function is a UFunction, this value will be set
- L25 _public member_ `TSubclassOf<UK2Node> ConversionNode;` — `UPROPERTY(BlueprintReadOnly, Category = "MVVM")` — If the conversion function is a UK2Node, this value will be set

#### class `UMVVMToolset`  
`class UMVVMToolset : public UToolsetDefinition`  
_L29-132_
- reflection: `UCLASS(BlueprintType, Hidden)`
- inherits: `UToolsetDefinition`
- L43 _public prototype_ `static UBlueprint* CreateViewModel(const FString& ViewModelName, const FString& PackagePath, UClass* ParentClass);` — `UFUNCTION(BlueprintCallable, meta = (Experimental, AICallable), Category = "MVVM")` — Creates a new ViewModel asset @param ViewModelName - Desired ViewModel asset name. @param PackagePath - Target path in which the asset should reside @param ParentClass - Class of which the ViewModel should derive. Must derive UMVVMViewModelBase @return newly created ViewModel blueprint.
- L55 _public prototype_ `static bool AddViewModelProperty(UBlueprint* ViewModel, const FString& PropertyName, const FString& PropertyType, const FString& DefaultValue);` — `UFUNCTION(BlueprintCallable, meta = (Experimental, AICallable), Category = "MVVM")` — Add a property to an existing ViewModel @param ViewModel - ViewModel asset to use. @param PropertyName - Desired name of the new property @param PropertyType - Desired type of the new property. Corresponds with PinType @param DefaultValue - If a default property is desired, string representation of the value @return True if property was succesfully added.
- L64 _public prototype_ `static TArray<UClass*> ListViewModels(const FString& SearchPath);` — `UFUNCTION(BlueprintCallable, meta = (Experimental, AICallable), Category = "MVVM")` — List all ViewModel under the search path @param SearchPath - Mount point search path for ViewModel assets @return List of ViewModel classes.
- L73 _public prototype_ `static TArray<UClass*> ListWidgetViewModels(UWidgetBlueprint* WidgetBlueprint);` — `UFUNCTION(BlueprintCallable, meta = (Experimental, AICallable), Category = "MVVM")` — List all ViewModel on the WidgetBlueprint @param WidgetBlueprint - WidgetBlueprint to use @return List of ViewModel classes.
- L82 _public prototype_ `static void AddViewModelToWidget(UWidgetBlueprint* WidgetBlueprint, UClass* ViewModelClass);` — `UFUNCTION(BlueprintCallable, meta = (Experimental, AICallable), Category = "MVVM")` — Adds a ViewModel to the WidgetBlueprint @param WidgetBlueprint - WidgetBlueprint to use @param ViewModelClass - ViewModel class to use.
- L91 _public prototype_ `static TArray<FMVVMBlueprintViewBinding> ListWidgetViewBindings(UWidgetBlueprint* WidgetBlueprint);` — `UFUNCTION(BlueprintCallable, meta = (Experimental, AICallable), Category = "MVVM")` — List all view bindings on the WidgetBlueprint @param WidgetBlueprint - WidgetBlueprint to use @return List of FMVVMBlueprintViewBinding that describe each available view binding.
- L100 _public prototype_ `static bool RemoveWidgetViewBinding(UWidgetBlueprint* WidgetBlueprint, const FGuid& BindingID);` — `UFUNCTION(BlueprintCallable, meta = (Experimental, AICallable), Category = "MVVM")` — Removes View Binding on the WidgetBlueprint @param WidgetBlueprint - WidgetBlueprint to use @return True if binding was removed.
- L123 _public prototype_ `static FGuid CreateViewBinding(UWidgetBlueprint* WidgetBlueprint, UObject* SourceContext, const FString& SourcePropertyPath, UObject* DestinationContext, const FString& DestinationPropertyPath, FName ConversionName);` — `UFUNCTION(BlueprintCallable, meta = (Experimental, AICallable), Category = "MVVM")` — Creates a View Binding from the SourceProperty to the Destination property. If there is a type mismatch, an existing conversion function will try to be used. @param WidgetBlueprint - WidgetBlueprint to use @param SourceContext - Source object that contains the source property. Can be the following: - UWidget: source property is from a widget in the widget blueprint's widgettree - UClass: source property is from a widget blueprint's ViewModel - Null: source property is from the widget blueprint @param SourcePropertyPath - Property to read data from. Contains a dot '.' separated path to the field (path.subfield) @param DestinationContext - Destination object that contains the destination property. Can be the following: - UWidget: destination property is from a widget in the widget blueprint's widgettree - UClass: destination property is from a widget blueprint's ViewModel - Null: destination property is from the widget blueprint @param DestinationPropertyPath - Property to write data to. Contains a dot '.' separated path to the field (path.subfield) @param ConversionName - Optional parameter, name of a conversion function to use if needed. If none is provided, this will be inferred. @return Valid FGuid if the binding was created
- L131 _public prototype_ `static TArray<FMVVMViewConversionFunctionDescription> ListConversionFunctions(UWidgetBlueprint* WidgetBlueprint);` — `UFUNCTION(BlueprintCallable, meta = (Experimental, AICallable), Category = "MVVM")` — List Available Conversion functions for a WidgetBlueprint that bind a Source Property to a Destination Property @param WidgetBlueprint - WidgetBlueprint to use @return the FMVVMViewConversionFunctionDescription for available conversion functions.
