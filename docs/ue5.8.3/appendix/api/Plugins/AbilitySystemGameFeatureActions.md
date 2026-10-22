# Plugins / AbilitySystemGameFeatureActions

- module root: `Plugins/Experimental/AbilitySystemGameFeatureActions/Source/AbilitySystemGameFeatureActions`
- headers: 1; symbols: 14
- symbol kinds: class=1, member=4, prototype=9
- PrivateDependencyModuleNames: GameFeatures, GameplayAbilities
- PublicDependencyModuleNames: Core, CoreUObject, DataRegistry, DeveloperSettings, Engine, ModularGameplay

### `Plugins/Experimental/AbilitySystemGameFeatureActions/Source/AbilitySystemGameFeatureActions/Public/GameFeatureAction_AddAttributeDefaults.h` (Public)


#### class `UGameFeatureAction_AddAttributeDefaults`  
`class UGameFeatureAction_AddAttributeDefaults final : public UGameFeatureAction`  
_L16-54_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Add Attribute Defaults"))`
- inherits: `UGameFeatureAction`
- desc: Adds ability system attribute defaults from this game feature
- L22 _public prototype_ `virtual void OnGameFeatureRegistering() override;`
- L23 _public prototype_ `virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;`
- L24 _public prototype_ `virtual void OnGameFeatureUnregistering() override;`
- L25 _public prototype_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;`
- L29 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L37 _public member_ `bool bApplyOnRegister = true;` — `UPROPERTY(EditAnywhere, Category = Attributes, AdvancedDisplay)` — True: Apply defaults when the game feature is registered. False: Apply defaults when the game feature is activated.
- L41 _public member_ `TArray<FSoftObjectPath> AttribDefaultTableNames;` — `UPROPERTY(EditAnywhere, Category = Attributes)` — List of attribute default tables to add
- L45 _private prototype_ `bool ShouldAddAttributeDefaults() const;`
- L46 _private prototype_ `bool ShouldRemoveAttributeDefaults() const;`
- L48 _private prototype_ `void AddAttributeDefaults();`
- L49 _private prototype_ `void RemoveAttributeDefaults();`
- L51 _private member_ `FName AttributeDefaultTablesOwnerName;`
- L53 _private member_ `bool bAttributesHaveBeenSet = false;`
