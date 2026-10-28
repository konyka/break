# Plugins / ModelViewViewModelDebugger

- module root: `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebugger`
- headers: 5; symbols: 63
- symbol kinds: class=1, enum=1, enumerator=3, function=4, macro=1, member=37, namespace=4, prototype=5, struct=7
- PrivateDependencyModuleNames: Slate, SlateCore, UMG
- PublicDependencyModuleNames: Core, CoreUObject, FieldNotification, ModelViewViewModel

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebugger/Public/MVVMDebugItemId.h` (Public)


#### struct `UE::MVVM::FDebugItemId`  
`struct FDebugItemId`  
_L10-30_
- L17 _public member_ `Invalid, View, ViewModel, } Type = EType::Invalid;`
- L18 _public member_ `FGuid Id;`
- L21 _public prototype_ `FDebugItemId() = default;`
- L22 _public function_ `FDebugItemId(EType InType, FGuid InId) : Type(InType), Id(InId)`
- L26 _public function_ `bool operator==(const FDebugItemId& Other) const`

#### enum `UE::MVVM::FDebugItemId::EType`  
`enum class EType : uint8`  
_L12-17_
- L14 _public enumerator_ `Invalid`
- L15 _public enumerator_ `View`
- L16 _public enumerator_ `ViewModel`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebugger/Public/MVVMDebugSnapshot.h` (Public)


#### class `UE::MVVM::FDebugSnapshot`  
`class FDebugSnapshot`  
_L20-44_
- L23 _private member_ `TArray<TSharedPtr<FMVVMViewDebugEntry>> Views;`
- L24 _private member_ `TArray<TSharedPtr<FMVVMViewClassDebugEntry>> ViewClasses;`
- L25 _private member_ `TArray<TSharedPtr<FMVVMViewModelDebugEntry>> ViewModels;`
- L28 _public function_ `TArrayView<TSharedPtr<FMVVMViewDebugEntry>> GetViews()`
- L32 _public function_ `TArrayView<TSharedPtr<FMVVMViewModelDebugEntry>> GetViewModels()`
- L37 _public prototype_ `TSharedPtr<FMVVMViewDebugEntry> FindView(FGuid Id) const;`
- L38 _public prototype_ `TSharedPtr<FMVVMViewModelDebugEntry> FindViewModel(FGuid Id) const;`
- L40 _public prototype_ `static TSharedPtr<FDebugSnapshot> CreateSnapshot();`
- L43 _private prototype_ `TSharedRef<FMVVMViewClassDebugEntry> FindOrAddViewClassEntry(const UMVVMViewClass* ViewClass);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELVIEWVIEWMODELDEBUGGER_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebugger/Public/MVVMDebugView.h` (Public)


#### struct `FMVVMViewSourceDebugEntry`  
`struct FMVVMViewSourceDebugEntry`  
_L15-29_
- reflection: `USTRUCT()`
- L20 _public member_ `FName SourceInstanceName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L23 _public member_ `FAssetData SourceAsset;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L26 _public member_ `FGuid ViewModelDebugId;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — if it exist and if it's a viewmodel
- L28 _public member_ `TWeakObjectPtr<UObject> LiveSource;` — TScriptInterface<INotifyFieldValueChanged>

#### struct `FMVVMViewDebugEntry`  
`struct FMVVMViewDebugEntry`  
_L33-59_
- reflection: `USTRUCT()`
- L38 _public member_ `FName UserWidgetInstanceName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L41 _public member_ `FName LocalPlayerName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L44 _public member_ `FName WorldName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L47 _public member_ `FAssetData UserWidgetAsset;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L50 _public member_ `TArray<FMVVMViewSourceDebugEntry> Sources;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L53 _public member_ `FGuid ViewClassDebugId;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L56 _public member_ `FGuid ViewInstanceDebugId;` — `UPROPERTY()`
- L58 _public member_ `TWeakObjectPtr<UMVVMView> LiveView;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebugger/Public/MVVMDebugViewClass.h` (Public)


#### struct `FMVVMViewBindingDebugEntry`  
`struct FMVVMViewBindingDebugEntry`  
_L15-33_
- reflection: `USTRUCT()`
- L20 _public member_ `FGuid BlueprintViewBindingId;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L23 _public member_ `FString SourceFieldPath;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L26 _public member_ `FString DestinationFieldPath;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L29 _public member_ `FString ConversionFunctionFieldPath;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L32 _public member_ `int32 CompiledBindingIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`

#### struct `FMVVMViewClassDebugEntry`  
`struct FMVVMViewClassDebugEntry`  
_L37-48_
- reflection: `USTRUCT()`
- L42 _public member_ `TArray<FMVVMViewBindingDebugEntry> Bindings;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L45 _public member_ `FGuid ViewClassDebugId;` — `UPROPERTY()`
- L47 _public member_ `TWeakObjectPtr<const UMVVMViewClass> LiveViewClass;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebugger/Public/MVVMDebugViewModel.h` (Public)


#### struct `FMVVMViewModelFieldBoundDebugEntry`  
`struct FMVVMViewModelFieldBoundDebugEntry`  
_L15-33_
- reflection: `USTRUCT()`
- L20 _public member_ `FName KeyObjectName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L23 _public member_ `FFieldNotificationId KeyFieldId;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L26 _public member_ `FString BindingObjectPathName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L29 _public member_ `FName BindingFunctionName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L31 _public member_ `TWeakObjectPtr<const UObject> LiveInstanceKeyObject;`
- L32 _public member_ `TWeakObjectPtr<const UObject> LiveInstanceBindingObject;`

#### struct `FMVVMViewModelDebugEntry`  
`struct FMVVMViewModelDebugEntry`  
_L37-60_
- reflection: `USTRUCT()`
- L42 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L45 _public member_ `FString PathName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L48 _public member_ `FAssetData ViewModelAsset;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L51 _public member_ `TArray<FMVVMViewModelFieldBoundDebugEntry> FieldBound;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L57 _public member_ `FGuid ViewModelDebugId;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L59 _public member_ `TWeakObjectPtr<UObject> LiveViewModel;`
