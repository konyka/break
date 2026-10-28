# Plugins / HairStrandsMutableEditor

- module root: `Plugins/Experimental/HairStrandsMutable/Source/HairStrandsMutableEditor`
- headers: 2; symbols: 14
- symbol kinds: class=1, member=2, prototype=11
- PrivateDependencyModuleNames: HairStrandsCore, HairStrandsMutable
- PublicDependencyModuleNames: Core, CoreUObject, CustomizableObjectEditor, Engine, MutableRuntime, MutableTools

### `Plugins/Experimental/HairStrandsMutable/Source/HairStrandsMutableEditor/Public/CustomizableObjectNodeGroomConstant.h` (Public)


#### class `UCustomizableObjectNodeGroomConstant`  
`class UCustomizableObjectNodeGroomConstant : public UCustomizableObjectNodeExtensionDataConstant, public ICustomizableObjectExtensionNode`  
_L13-45_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeExtensionDataConstant,ICustomizableObjectExtensionNode`
- desc: Imports a Groom into the Customizable Object graph
- L18 _public prototype_ `UCustomizableObjectNodeGroomConstant();`
- L21 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L24 _public prototype_ `virtual void PostLoad() override;`
- L25 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L29 _public prototype_ `virtual bool ShouldAddToContextMenu(FText& OutCategory) const override;`
- L30 _public prototype_ `virtual bool IsExperimental() const override;`
- L33 _public prototype_ `virtual UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeExtensionData> GenerateMutableNode(FExtensionDataCompilerInterface& CompilerInterface) const override;` — ICustomizableObjectExtensionNode interface
- L37 _private prototype_ `void CopyCompiledData();` — Own interface
- L40 _private member_ `FGroomPinData GroomData;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L43 _private member_ `TObjectPtr<UGroomCompiledData> CompiledData;` — `UPROPERTY()`

### `Plugins/Experimental/HairStrandsMutable/Source/HairStrandsMutableEditor/Public/HairStrandsMutableEditorModule.h` (Public)
_(no declarations extracted)_
