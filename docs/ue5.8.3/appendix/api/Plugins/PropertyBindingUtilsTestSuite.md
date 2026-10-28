# Plugins / PropertyBindingUtilsTestSuite

- module root: `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtilsTestSuite`
- headers: 2; symbols: 22
- symbol kinds: class=4, function=2, member=14, struct=2
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AITestSuite, Core, CoreUObject, Engine, PropertyBindingUtils

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtilsTestSuite/Private/PropertyBindingUtilsTest.h` (Private)


#### struct `FPropertyBindingUtilsTest_PropertyStructB`  
`struct FPropertyBindingUtilsTest_PropertyStructB`  
_L10-16_
- reflection: `USTRUCT()`
- L15 _public member_ `int32 B = 0;` — `UPROPERTY(EditAnywhere, Category = "")`

#### struct `FPropertyBindingUtilsTest_PropertyStruct`  
`struct FPropertyBindingUtilsTest_PropertyStruct`  
_L19-31_
- reflection: `USTRUCT()`
- L24 _public member_ `int32 A = 0;` — `UPROPERTY(EditAnywhere, Category = "")`
- L27 _public member_ `int32 B = 0;` — `UPROPERTY(EditAnywhere, Category = "")`
- L30 _public member_ `FPropertyBindingUtilsTest_PropertyStructB StructB;` — `UPROPERTY(EditAnywhere, Category = "")`

#### class `UPropertyBindingUtilsTest_PropertyObjectInstanced`  
`class UPropertyBindingUtilsTest_PropertyObjectInstanced : public UObject`  
_L34-44_
- reflection: `UCLASS(HideDropdown)`
- inherits: `UObject`
- L40 _public member_ `int32 A = 0;` — `UPROPERTY(EditAnywhere, Category = "")`
- L43 _public member_ `FInstancedStruct InstancedStruct;` — `UPROPERTY(EditAnywhere, Category = "")`

#### class `UPropertyBindingUtilsTest_PropertyObjectInstancedWithB`  
`class UPropertyBindingUtilsTest_PropertyObjectInstancedWithB : public UPropertyBindingUtilsTest_PropertyObjectInstanced`  
_L47-54_
- reflection: `UCLASS(HideDropdown)`
- inherits: `UPropertyBindingUtilsTest_PropertyObjectInstanced`
- L53 _public member_ `int32 B = 0;` — `UPROPERTY(EditAnywhere, Category = "")`

#### class `UPropertyBindingUtilsTest_PropertyObject`  
`class UPropertyBindingUtilsTest_PropertyObject : public UObject`  
_L57-82_
- reflection: `UCLASS(HideDropdown)`
- inherits: `UObject`
- L63 _public member_ `TObjectPtr<UPropertyBindingUtilsTest_PropertyObjectInstanced> InstancedObject;` — `UPROPERTY(EditAnywhere, Instanced, Category = "")`
- L66 _public member_ `TArray<TObjectPtr<UPropertyBindingUtilsTest_PropertyObjectInstanced>> ArrayOfInstancedObjects;` — `UPROPERTY(EditAnywhere, Instanced, Category = "")`
- L69 _public member_ `TArray<int32> ArrayOfInts;` — `UPROPERTY(EditAnywhere, Category = "")`
- L72 _public member_ `FInstancedStruct InstancedStruct;` — `UPROPERTY(EditAnywhere, Category = "")`
- L75 _public member_ `TArray<FInstancedStruct> ArrayOfInstancedStructs;` — `UPROPERTY(EditAnywhere, Category = "")`
- L78 _public member_ `FPropertyBindingUtilsTest_PropertyStruct Struct;` — `UPROPERTY(EditAnywhere, Category = "")`
- L81 _public member_ `TArray<FPropertyBindingUtilsTest_PropertyStruct> ArrayOfStruct;` — `UPROPERTY(EditAnywhere, Category = "")`

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtilsTestSuite/Public/PropertyBindingUtilsTestSuiteModule.h` (Public)


#### class `IPropertyBindingUtilsTestSuiteModule`  
`class IPropertyBindingUtilsTestSuiteModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IPropertyBindingUtilsTestSuiteModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
