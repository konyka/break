# Plugins / AnimationSharingEd

- module root: `Plugins/Developer/AnimationSharing/Source/AnimationSharingEd`
- headers: 4; symbols: 48
- symbol kinds: class=6, function=9, member=7, namespace=1, prototype=25
- PrivateDependencyModuleNames: AnimationSharing, AssetTools, Core, CoreUObject, PropertyEditor, Slate, SlateCore, UnrealEd

### `Plugins/Developer/AnimationSharing/Source/AnimationSharingEd/Public/AnimationSharingEdModule.h` (Public)


#### class `FAnimSharingEdModule`  
`class FAnimSharingEdModule : public IModuleInterface`  
_L10-19_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L13 _public function_ `FAnimSharingEdModule()`
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`
- L18 _private member_ `class FAssetTypeActions_AnimationSharingSetup* AssetAction;`

### `Plugins/Developer/AnimationSharing/Source/AnimationSharingEd/Public/AnimationSharingSetupFactory.h` (Public)


#### class `UAnimationSharingSetupFactory`  
`class UAnimationSharingSetupFactory : public UFactory`  
_L12-20_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L18 _private prototype_ `virtual uint32 GetMenuCategories() const;`

### `Plugins/Developer/AnimationSharing/Source/AnimationSharingEd/Public/AssetTypeActions_AnimationSharingSetup.h` (Public)


#### class `FAssetTypeActions_AnimationSharingSetup`  
`class FAssetTypeActions_AnimationSharingSetup : public FAssetTypeActions_Base`  
_L8-24_
- inherits: `FAssetTypeActions_Base`
- L12 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L13 _public function_ `virtual FColor GetTypeColor() const override`
- L14 _public function_ `virtual UClass* GetSupportedClass() const override`
- L15 _public function_ `virtual uint32 GetCategories() override`
- L16 _public function_ `virtual const TArray<FText>& GetSubMenus() const override`

### `Plugins/Developer/AnimationSharing/Source/AnimationSharingEd/Public/SetupDetailsViewCustomizations.h` (Public)


#### class `FPerSkeletonAnimationSharingSetupCustomization`  
`class FPerSkeletonAnimationSharingSetupCustomization : public IPropertyTypeCustomization`  
_L11-28_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L16 _public function_ `FPerSkeletonAnimationSharingSetupCustomization()`
- L17 _public prototype_ `virtual ~FPerSkeletonAnimationSharingSetupCustomization() = default;`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — Begin IPropertyTypeCustomization interface
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L25 _protected prototype_ `FText GetSkeletonName() const;`
- L27 _protected member_ `TSharedPtr<IPropertyHandle> SkeletonPropertyHandle;`

#### class `FAnimationStateEntryCustomization`  
`class FAnimationStateEntryCustomization : public IPropertyTypeCustomization`  
_L30-57_
- inherits: `IPropertyTypeCustomization`
- L33 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L35 _public function_ `FAnimationStateEntryCustomization() : StatePropertyHandle(nullptr), ProcessorPropertyHandle(nullptr), CachedComboBoxEnumClass(nullptr)`
- L36 _public prototype_ `virtual ~FAnimationStateEntryCustomization() = default;`
- L39 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — Begin IPropertyTypeCustomization interface
- L40 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L44 _protected prototype_ `FText GetStateName(TSharedPtr<IPropertyHandle> PropertyHandle) const;`
- L45 _protected prototype_ `FDetailWidgetRow& CreateEnumSelectionWidget(TSharedRef<IPropertyHandle> ChildHandle, IDetailChildrenBuilder& StructBuilder);`
- L46 _protected prototype_ `const TArray<TSharedPtr<FString>> GetComboBoxSourceItems() const;`
- L47 _protected prototype_ `const TSharedPtr<FString> GetSelectedEnum(TSharedPtr<IPropertyHandle> PropertyHandle) const;`
- L48 _protected prototype_ `void SelectedEnumChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo, TSharedRef<IPropertyHandle> PropertyHandle);`
- L49 _protected prototype_ `void GenerateEnumComboBoxItems();`
- L52 _protected member_ `TSharedPtr<IPropertyHandle> StatePropertyHandle;`
- L53 _protected member_ `TSharedPtr<IPropertyHandle> ProcessorPropertyHandle;`
- L55 _protected member_ `UEnum* CachedComboBoxEnumClass;`
- L56 _protected member_ `TArray<TSharedPtr<FString>> ComboBoxItems;`

#### class `FAnimationSetupCustomization`  
`class FAnimationSetupCustomization : public IPropertyTypeCustomization`  
_L59-77_
- inherits: `IPropertyTypeCustomization`
- L62 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L64 _public function_ `FAnimationSetupCustomization()`
- L65 _public prototype_ `virtual ~FAnimationSetupCustomization() = default;`
- L68 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — Begin IPropertyTypeCustomization interface
- L69 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L73 _protected prototype_ `FText GetAnimationName(TSharedPtr<IPropertyHandle> PropertyHandle) const;`
- L76 _protected member_ `TSharedPtr<IPropertyHandle> AnimSequencePropertyHandle;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ESelectInfo`
- L9 _prototype_ `static UEnum* GetStateEnumClass(const TSharedPtr<IPropertyHandle>& InProperty);`
