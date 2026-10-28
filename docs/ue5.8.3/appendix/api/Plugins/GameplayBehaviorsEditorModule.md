# Plugins / GameplayBehaviorsEditorModule

- module root: `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsEditorModule`
- headers: 2; symbols: 10
- symbol kinds: class=2, function=2, member=2, prototype=4
- PrivateDependencyModuleNames: BehaviorTreeEditor
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GameplayBehaviorsModule, SlateCore

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsEditorModule/Private/GameplayBehaviorsEditorStyle.h` (Private)


#### class `FGameplayBehaviorsEditorStyle`  
`class FGameplayBehaviorsEditorStyle final : public FSlateStyleSet`  
_L7-21_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `virtual ~FGameplayBehaviorsEditorStyle();`
- L12 _public prototype_ `static FGameplayBehaviorsEditorStyle& Get();`
- L13 _public prototype_ `static void Shutdown();`
- L15 _public member_ `static FColor GameplayTagTypeColor;`
- L18 _private prototype_ `FGameplayBehaviorsEditorStyle();`
- L20 _private member_ `static TUniquePtr<FGameplayBehaviorsEditorStyle> Instance;`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsEditorModule/Public/GameplayBehaviorsEditorModule.h` (Public)


#### class `IGameplayBehaviorsEditorModule`  
`class IGameplayBehaviorsEditorModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IGameplayBehaviorsEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
