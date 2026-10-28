# Plugins / ACLPluginEditor

- module root: `Plugins/Animation/ACLPlugin/Source/ACLPluginEditor`
- headers: 5; symbols: 36
- symbol kinds: class=5, function=7, member=16, prototype=8
- PrivateDependencyModuleNames: EditorStyle, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: ACLPlugin, AnimationDataController, Core, CoreUObject, Engine

### `Plugins/Animation/ACLPlugin/Source/ACLPluginEditor/Classes/ACLDatabaseBuildCommandlet.h` (Public)


#### class `UACLDatabaseBuildCommandlet`  
`class UACLDatabaseBuildCommandlet : public UCommandlet`  
_L13-19_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: This commandlet is used to update instances of UAnimationCompressionLibraryDatabase to ensure their mapping is up-to-date.
- L18 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Animation/ACLPlugin/Source/ACLPluginEditor/Classes/ACLStatsDumpCommandlet.h` (Public)


#### class `UACLStatsDumpCommandlet`  
`class UACLStatsDumpCommandlet : public UCommandlet`  
_L15-40_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: This commandlet is used to extract and dump animation compression statistics. See cpp implementation for example usage and supported arguments.
- L20 _public prototype_ `virtual int32 Main(const FString& Params) override;`
- L22 _public member_ `FString ACLRawDir;`
- L23 _public member_ `FString OutputDir;`
- L25 _public member_ `bool PerformExhaustiveDump;`
- L26 _public member_ `bool PerformCompression;`
- L27 _public member_ `bool PerformClipExtraction;`
- L28 _public member_ `bool TryAutomaticCompression;`
- L29 _public member_ `bool TryACLCompression;`
- L30 _public member_ `bool TryKeyReductionRetarget;`
- L31 _public member_ `bool TryKeyReduction;`
- L32 _public member_ `bool ResumeTask;`
- L33 _public member_ `bool SkipAdditiveClips;`
- L35 _public member_ `class UAnimBoneCompressionSettings* AutoCompressionSettings;`
- L36 _public member_ `class UAnimBoneCompressionSettings* ACLCompressionSettings;`
- L37 _public member_ `class UAnimBoneCompressionSettings* KeyReductionCompressionSettings;`
- L38 _public member_ `class UAnimBoneCompressionCodec_ACL* ACLCodec;`
- L39 _public member_ `class UAnimCompress_RemoveLinearKeys* KeyReductionCodec;`

### `Plugins/Animation/ACLPlugin/Source/ACLPluginEditor/Classes/AnimationCompressionLibraryDatabaseFactory.h` (Public)


#### class `UAnimationCompressionLibraryDatabaseFactory`  
`class UAnimationCompressionLibraryDatabaseFactory : public UFactory`  
_L11-18_
- reflection: `UCLASS(HideCategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Animation/ACLPlugin/Source/ACLPluginEditor/Private/AssetTypeActions_AnimationCompressionLibraryDatabase.h` (Private)


#### class `FAssetTypeActions_AnimationCompressionLibraryDatabase`  
`class FAssetTypeActions_AnimationCompressionLibraryDatabase : public FAssetTypeActions_Base`  
_L10-28_
- inherits: `FAssetTypeActions_Base`
- L14 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L15 _public function_ `virtual FColor GetTypeColor() const override`
- L16 _public function_ `virtual UClass* GetSupportedClass() const override`
- L17 _public function_ `virtual bool CanFilter() override`
- L18 _public function_ `virtual uint32 GetCategories() override`
- L19 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const override;`
- L21 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L23 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;`
- L26 _private prototype_ `void AddToolbarExtension(FToolBarBuilder& Builder, TWeakObjectPtr<UAnimationCompressionLibraryDatabase> DatabasePtr);`
- L27 _private prototype_ `void ExecuteBuild(TWeakObjectPtr<UAnimationCompressionLibraryDatabase> DatabasePtr);`

### `Plugins/Animation/ACLPlugin/Source/ACLPluginEditor/Public/IACLPluginEditorModule.h` (Public)


#### class `IACLPluginEditor`  
`class IACLPluginEditor : public IModuleInterface`  
_L11-23_
- inherits: `IModuleInterface`
- desc: The editor ACL plugin module interface.
- L14 _public function_ `static inline IACLPluginEditor& Get()`
- L19 _public function_ `static inline bool IsAvailable()`
