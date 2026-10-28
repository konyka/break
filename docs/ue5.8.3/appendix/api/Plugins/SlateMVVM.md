# Plugins / SlateMVVM

- module root: `Plugins/Experimental/SlateModelViewViewModel/Source/SlateMVVM`
- headers: 1; symbols: 39
- symbol kinds: class=1, function=5, member=4, namespace=4, prototype=22, struct=2, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject, FieldNotification, SlateCore

### `Plugins/Experimental/SlateModelViewViewModel/Source/SlateMVVM/Public/SlateViewModelBindings.h` (Public)


#### struct `UE::Slate::MVVM::FSourceInstanceId`  
`struct FSourceInstanceId`  
_L16-46_
- L21 _public prototype_ `FSourceInstanceId() = default;`
- L23 _public function_ `bool IsValid() const`
- L28 _public function_ `explicit operator bool() const`
- L33 _public function_ `bool operator ==(const FSourceInstanceId& Other) const`
- L44 _private prototype_ `static FSourceInstanceId Create(const UObject* Object);`
- L45 _private member_ `FObjectKey ObjectKey;`

#### class `UE::Slate::MVVM::FViewModelBindings`  
`class FViewModelBindings`  
_L48-136_
- L51 _public typedef_ `using FEvaluateSourceDelegate = TDelegate<UObject*()>;`
- L76 _public prototype_ `FViewModelBindings();`
- L77 _public prototype_ `FViewModelBindings(const FViewModelBindings&) = delete;`
- L78 _public prototype_ `FViewModelBindings& operator=(const FViewModelBindings&) = delete;`
- L81 _public prototype_ `FBuilder AddSource(TScriptInterface<INotifyFieldValueChanged> Value);` — Add a source that can provide notification when a value changes.
- L87 _public prototype_ `void RemoveSource(FSourceInstanceId Source);` — Add a source that can provide notification when a value changes. It will evaluate the dependencies.
- L93 _public prototype_ `void SetSource(FSourceInstanceId Source, TScriptInterface<INotifyFieldValueChanged> Value);` — Set the new source value of a created source. It will evaluate the dependencies and execute the bindings of that source.
- L96 _public prototype_ `void AddBinding(FSourceInstanceId Source, UE::FieldNotification::FFieldId WhenFieldId, INotifyFieldValueChanged::FFieldValueChangedDelegate Delegate);` — Add a delegate to execute when a field changed.
- L99 _public prototype_ `void AddBinding(FSourceInstanceId Source, UE::FieldNotification::FFieldId WhenFieldId, FSimpleDelegate Delegate);` — Add a delegate to execute when a field changed.
- L105 _public prototype_ `void RemoveAllBindings(FSourceInstanceId Source);` — Remove all added delegates from that source.
- L112 _public prototype_ `void AddDependency(FSourceInstanceId ToEvaluate, FSourceInstanceId WhenChanged, FEvaluateSourceDelegate EvaluateDelegate);` — The source ToEvaluate depends on the source WhenChanged. When the WhenChanged value changes via SetSource, execute all ToEvaluate bindings. It may cascade to evaluate dependency of dependency.
- L120 _public prototype_ `void AddDependency(FSourceInstanceId ToEvaluate, FSourceInstanceId WhenChanged, UE::FieldNotification::FFieldId WhenFieldId, FEvaluateSourceDelegate EvaluateDelegate);` — The source ToEvaluate depends on the source WhenChanged. When the WhenChanged value changes via SetSource, execute all ToEvaluate bindings. Also, when the WhenField triggers, execute all ToEvalute bindings. It may cascade to evaluate dependency of dependency.
- L126 _public prototype_ `void Execute();` — Execute the bindings of all the sources. The Dependency will be executed only if the FieldId changes (executing a binding, trigger a modification that execute another binding).
- L132 _public prototype_ `void Execute(FSourceInstanceId Source);` — Execute the bindings for that source. The Dependency will be executed only if the FieldId changes (executing a binding, trigger a modification that execute another binding).
- L135 _private member_ `TPimplPtr<Private::FViewModelBindingsImpl> Impl;`

#### struct `UE::Slate::MVVM::FViewModelBindings::FBuilder`  
`struct FBuilder`  
_L54-73_
- L56 _public prototype_ `FBuilder(Private::FViewModelBindingsImpl& Instance, FSourceInstanceId Id);`
- L57 _public prototype_ `FBuilder(const FBuilder&) = delete;`
- L58 _public prototype_ `FBuilder& operator=(const FBuilder&) = delete;`
- L60 _public prototype_ `FBuilder& AddBinding(UE::FieldNotification::FFieldId WhenFieldId, INotifyFieldValueChanged::FFieldValueChangedDelegate Delegate);`
- L61 _public prototype_ `FBuilder& AddBinding(UE::FieldNotification::FFieldId WhenFieldId, FSimpleDelegate Delegate);`
- L62 _public prototype_ `FBuilder& AddDependency(FSourceInstanceId WhenChanged, FViewModelBindings::FEvaluateSourceDelegate EvaluateDelegate);`
- L63 _public prototype_ `FBuilder& AddDependency(FSourceInstanceId WhenChanged, UE::FieldNotification::FFieldId WhenFieldId, FViewModelBindings::FEvaluateSourceDelegate EvaluateDelegate);`
- L65 _public function_ `FSourceInstanceId GetId() const`
- L71 _private member_ `Private::FViewModelBindingsImpl& Instance;`
- L72 _private member_ `FSourceInstanceId Id;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Slate` (scope `UE`)
- L11 _namespace_ `namespace MVVM` (scope `UE::Slate`)
- L14 _namespace_ `namespace Private` (scope `UE::Slate::MVVM`)
- L38 _function_ `friend uint32 GetTypeHash(const FSourceInstanceId& Key)` (scope `UE::Slate::MVVM`)
