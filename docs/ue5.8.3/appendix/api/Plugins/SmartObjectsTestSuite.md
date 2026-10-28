# Plugins / SmartObjectsTestSuite

- module root: `Plugins/Runtime/SmartObjects/Source/SmartObjectsTestSuite`
- headers: 2; symbols: 15
- symbol kinds: class=4, function=3, member=2, prototype=4, struct=2
- PrivateDependencyModuleNames: EditorFramework, UnrealEd

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsTestSuite/Public/SmartObjectTestTypes.h` (Public)


#### class `USmartObjectTestBehaviorDefinition`  
`class USmartObjectTestBehaviorDefinition : public USmartObjectBehaviorDefinition`  
_L12-15_
- reflection: `UCLASS(MinimalAPI, HideDropdown, NotBlueprintType)`
- inherits: `USmartObjectBehaviorDefinition`
- desc: Concrete definition class for testing purposes

#### class `USmartObjectTestSubsystem`  
`class USmartObjectTestSubsystem : public USmartObjectSubsystem`  
_L21-34_
- reflection: `UCLASS(HideDropdown, NotBlueprintType)`
- inherits: `USmartObjectSubsystem`
- desc: Test-time SmartObjectSubsystem override, aimed at encapsulating test-time smart object instances and functionality
- L26 _public prototype_ `USmartObjectTestSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L28 _public prototype_ `void RebuildAndInitializeForTesting();`
- L33 _protected function_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const`

#### class `ASmartObjectTestCollection`  
`class ASmartObjectTestCollection : public ASmartObjectPersistentCollection`  
_L40-47_
- reflection: `UCLASS(HideDropdown, NotBlueprintType)`
- inherits: `ASmartObjectPersistentCollection`
- desc: Test-time ASmartObjectPersistentCollection override, aimed at encapsulating test-time smart object instances and functionality
- L45 _public prototype_ `virtual bool RegisterWithSubsystem(const FString& Context) override;`
- L46 _public prototype_ `virtual bool UnregisterWithSubsystem(const FString& Context) override;`

#### struct `FSmartObjectSlotTestDefinitionData`  
`struct FSmartObjectSlotTestDefinitionData: public FSmartObjectDefinitionData`  
_L53-58_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FSmartObjectDefinitionData`
- desc: Some user data to assign to a slot definition
- L57 _public member_ `float SomeSharedFloat= 0.f;`

#### struct `FSmartObjectSlotTestRuntimeData`  
`struct FSmartObjectSlotTestRuntimeData : public FSmartObjectSlotStateData`  
_L64-69_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FSmartObjectSlotStateData`
- desc: Some user runtime data to assign to a slot instance
- L68 _public member_ `float SomePerInstanceSharedFloat = 0.0f;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsTestSuite/Public/SmartObjectsTestSuiteModule.h` (Public)


#### class `ISmartObjectsTestSuiteModule`  
`class ISmartObjectsTestSuiteModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline ISmartObjectsTestSuiteModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
