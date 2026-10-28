# Plugins / HairStrandsMutable

- module root: `Plugins/Experimental/HairStrandsMutable/Source/HairStrandsMutable`
- headers: 2; symbols: 26
- symbol kinds: class=2, member=19, prototype=4, struct=1
- PrivateDependencyModuleNames: Niagara
- PublicDependencyModuleNames: Core, CoreUObject, CustomizableObject, Engine, HairStrandsCore

### `Plugins/Experimental/HairStrandsMutable/Source/HairStrandsMutable/Public/HairStrandsMutableExtension.h` (Public)


#### struct `FGroomPinData`  
`struct FGroomPinData`  
_L18-54_
- reflection: `USTRUCT()`
- desc: Used as ExtensionData to represent a Groom Asset in a Customizable Object graph
- L25 _public member_ `FName ComponentName;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Name of the mesh component this groom will be attached to
- L29 _public member_ `TObjectPtr<UGroomAsset> GroomAsset;` — `UPROPERTY(EditAnywhere, Category = Groom)` — The groom asset to use. See UGroomComponent::GroomAsset.
- L33 _public member_ `TObjectPtr<UGroomCache> GroomCache;` — `UPROPERTY(EditAnywhere, Category = GroomCache, meta = (EditCondition = "BindingAsset == nullptr"))` — See UGroomComponent::GroomCache.
- L37 _public member_ `TObjectPtr<UGroomBindingAsset> BindingAsset;` — `UPROPERTY(EditAnywhere, Category = Groom, meta = (EditCondition = "GroomCache == nullptr"))` — See UGroomComponent::BindingAsset.
- L41 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(EditAnywhere, Category = Simulation)` — See UGroomComponent::PhysicsAsset.
- L45 _public member_ `FString AttachmentName;` — `UPROPERTY(EditAnywhere, Category = Groom)` — See UGroomComponent::AttachmentName.
- L49 _public member_ `FName GroomComponentName;` — `UPROPERTY(EditAnywhere, Category = Groom)` — Name of the created groom component
- L53 _public member_ `TArray<TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = Rendering)` — See UMeshComponent::OverrideMaterials.

#### class `UGroomCompiledData`  
`class UGroomCompiledData : public UObject`  
_L57-93_
- reflection: `UCLASS()`
- inherits: `UObject`
- L64 _public member_ `FName ComponentName;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Name of the mesh component this groom will be attached to
- L68 _public member_ `TObjectPtr<UGroomAsset> GroomAsset;` — `UPROPERTY(EditAnywhere, Category = Groom)` — The groom asset to use. See UGroomComponent::GroomAsset.
- L72 _public member_ `TObjectPtr<UGroomCache> GroomCache;` — `UPROPERTY(EditAnywhere, Category = GroomCache, meta = (EditCondition = "BindingAsset == nullptr"))` — See UGroomComponent::GroomCache.
- L76 _public member_ `TObjectPtr<UGroomBindingAsset> BindingAsset;` — `UPROPERTY(EditAnywhere, Category = Groom, meta = (EditCondition = "GroomCache == nullptr"))` — See UGroomComponent::BindingAsset.
- L80 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(EditAnywhere, Category = Simulation)` — See UGroomComponent::PhysicsAsset.
- L84 _public member_ `FString AttachmentName;` — `UPROPERTY(EditAnywhere, Category = Groom)` — See UGroomComponent::AttachmentName.
- L88 _public member_ `FName GroomComponentName;` — `UPROPERTY(EditAnywhere, Category = Groom)` — Name of the created groom component
- L92 _public member_ `TArray<TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = Rendering)` — See UMeshComponent::OverrideMaterials.

#### class `UHairStrandsMutableExtension`  
`class UHairStrandsMutableExtension : public UCustomizableObjectExtension`  
_L100-114_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectExtension`
- desc: An extension for Mutable that allows users to bring Grooms from the HairStrands plugin into their Customizable Objects
- L106 _public prototype_ `virtual TArray<FCustomizableObjectPinType> GetPinTypes() const override;` — UCustomizableObjectExtension interface
- L107 _public prototype_ `virtual TArray<FObjectNodeInputPin> GetAdditionalObjectNodePins() const override;`
- L108 _public prototype_ `virtual void OnCustomizableObjectInstanceUsageUpdated(UCustomizableObjectInstanceUsage& Usage, TArray<TObjectPtr<const UObject>>& ExtensionData) const override;`
- L109 _public prototype_ `virtual void OnCustomizableObjectInstanceUsageDiscarded(UCustomizableObjectInstanceUsage& Usage) const override;`
- L111 _public member_ `static const FName GroomPinType;`
- L112 _public member_ `static const FName GroomsBaseNodePinName;`
- L113 _public member_ `static const FText GroomNodeCategory;`

### `Plugins/Experimental/HairStrandsMutable/Source/HairStrandsMutable/Public/HairStrandsMutableModule.h` (Public)
_(no declarations extracted)_
