# Plugins / RazerChromaEditor

- module root: `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaEditor`
- headers: 2; symbols: 17
- symbol kinds: class=2, member=1, prototype=14
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MediaAssets, Projects, RazerChromaDevices, RazerChromaSDK, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaEditor/Private/RazerChromaAnimationAssetActions.h` (Private)


#### class `FAssetTypeActions_RazerChromaPreviewAction`  
`class FAssetTypeActions_RazerChromaPreviewAction : public FAssetTypeActions_Base`  
_L13-33_
- inherits: `FAssetTypeActions_Base`
- desc: Asset Actions for the URazerChromaAnimationAsset which allow you to preview the animation in the editor without having to PIE.
- L16 _public prototype_ `FAssetTypeActions_RazerChromaPreviewAction(const uint32 InCategoryBit);`
- L18 _public prototype_ `virtual FText GetName() const override;`
- L19 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L20 _public prototype_ `virtual uint32 GetCategories() override;`
- L21 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L22 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;`
- L23 _public prototype_ `virtual bool AssetsActivatedOverride(const TArray<UObject*>& InObjects, EAssetTypeActivationMethod::Type ActivationType) override;`
- L24 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`
- L28 _protected prototype_ `void ExecutePlayAnim(TArray<TWeakObjectPtr<URazerChromaAnimationAsset>> Objects);`
- L29 _protected prototype_ `void ExecuteStopAnim(TArray<TWeakObjectPtr<URazerChromaAnimationAsset>> Objects);`
- L30 _protected prototype_ `bool CanExecutePlayCommand(TArray<TWeakObjectPtr<URazerChromaAnimationAsset>> Objects) const;`
- L32 _protected member_ `uint32 CategoryBit;`

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaEditor/Private/RazerChromaFactory.h` (Private)


#### class `URazerChromaFactory`  
`class URazerChromaFactory : public UFactory`  
_L11-25_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L17 _public prototype_ `URazerChromaFactory(const FObjectInitializer& ObjectInitializer);`
- L22 _protected prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L23 _protected prototype_ `virtual UObject* FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn) override;`
