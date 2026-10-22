# Editor / SkeletonEditor

- module root: `Source/Editor/SkeletonEditor`
- headers: 28; symbols: 896
- symbol kinds: class=26, delegate=11, enum=9, enumerator=31, externvar=12, function=96, macro=6, member=195, namespace=6, prototype=495, struct=7, typedef=2
- DynamicallyLoadedModuleNames: MeshBoneReduction, PropertyEditor
- PrivateDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationCore, AnimationWidgets, ApplicationCore, AssetRegistry, BlueprintGraph, ContentBrowser, Core, CoreUObject, EditorFramework, EditorWidgets, Engine, InputCore, Kismet, Persona, PinnedCommandList, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: MeshBoneReduction, PropertyEditor
- PublicIncludePathModuleNames: AnimationWidgets, Persona

### `Source/Editor/SkeletonEditor/Private/BoneProxyDetailsCustomization.h` (Private)


#### class `FBoneProxyDetailsCustomization`  
`class FBoneProxyDetailsCustomization : public IDetailCustomization`  
_L13-49_
- inherits: `IDetailCustomization`
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L26 _private prototype_ `bool IsResetLocationVisible(TSharedPtr<IPropertyHandle> InPropertyHandle, TArrayView<UBoneProxy*> InBoneProxies);` — Handle reset to defaults visibility
- L29 _private prototype_ `bool IsResetRotationVisible(TSharedPtr<IPropertyHandle> InPropertyHandle, TArrayView<UBoneProxy*> InBoneProxies);` — Handle reset to defaults visibility
- L32 _private prototype_ `bool IsResetScaleVisible(TSharedPtr<IPropertyHandle> InPropertyHandle, TArrayView<UBoneProxy*> InBoneProxies);` — Handle reset to defaults visibility
- L35 _private prototype_ `void HandleResetLocation(TSharedPtr<IPropertyHandle> InPropertyHandle, TArrayView<UBoneProxy*> InBoneProxies);` — Handle resetting defaults
- L38 _private prototype_ `void HandleResetRotation(TSharedPtr<IPropertyHandle> InPropertyHandle, TArrayView<UBoneProxy*> InBoneProxies);` — Handle resetting defaults
- L41 _private prototype_ `void HandleResetScale(TSharedPtr<IPropertyHandle> InPropertyHandle, TArrayView<UBoneProxy*> InBoneProxies);` — Handle resetting defaults
- L44 _private prototype_ `void RemoveUnnecessaryModifications(UDebugSkelMeshComponent* Component, FAnimNode_ModifyBone& ModifyBone);` — Remove any modification node if it has no effect
- L48 _private member_ `TArray<UBoneProxy*> BoneProxies;` — Cached array of selected bone proxies

### `Source/Editor/SkeletonEditor/Private/EditableSkeleton.h` (Private)


#### class `FEditableSkeleton`  
`class FEditableSkeleton : public IEditableSkeleton, public FGCObject, public TSharedFromThis<FEditableSkeleton>`  
_L21-174_
- inherits: `IEditableSkeleton,FGCObject,TSharedFromThis<FEditableSkeleton>`
- desc: View-model for a skeleton tree
- L25 _public member_ `static const FString SocketCopyPasteHeader;` — String used as a header for text based copy-paste of sockets
- L28 _public prototype_ `FEditableSkeleton(USkeleton* InSkeleton);`
- L31 _public prototype_ `virtual const USkeleton& GetSkeleton() const override;` — IEditableSkeleton interface
- L32 _public prototype_ `virtual bool IsSkeletonValid() const override;`
- L33 _public prototype_ `virtual const TArray<class UBlendProfile*>& GetBlendProfiles() const override;`
- L34 _public prototype_ `virtual class UBlendProfile* GetBlendProfile(const FName& InBlendProfileName) override;`
- L35 _public prototype_ `virtual class UBlendProfile* CreateNewBlendProfile(const FName& InBlendProfileName) override;`
- L36 _public prototype_ `virtual void RemoveBlendProfile(UBlendProfile* InBlendProfile) override;`
- L37 _public prototype_ `virtual UBlendProfile* RenameBlendProfile(const FName& InBlendProfileName, const FName& InNewBlendProfileName) override;`
- L38 _public prototype_ `virtual void SetBlendProfileScale(const FName& InBlendProfileName, const FName& InBoneName, float InNewScale, bool bInRecurse) override;`
- L39 _public prototype_ `virtual void SetBlendProfileMode(FName InBlendProfileName, EBlendProfileMode ProfileMode);`
- L40 _public prototype_ `virtual USkeletalMeshSocket* DuplicateSocket(const FSelectedSocketInfo& SocketInfoToDuplicate, const FName& NewParentBoneName, USkeletalMesh* InSkeletalMesh) override;`
- L41 _public prototype_ `virtual int32 ValidatePreviewAttachedObjects() override;`
- L42 _public prototype_ `virtual int32 DeleteAnimNotifies(const TArray<FName>& InSelectedNotifyNames, bool bDeleteFromAnimations = true) override;`
- L43 _public prototype_ `virtual int32 DeleteSyncMarkers(const TArray<FName>& ISyncMarkerNames, bool bDeleteFromAnimations = true) override;`
- L44 _public prototype_ `virtual void AddNotify(FName NewName) override;`
- L45 _public prototype_ `virtual void AddSyncMarker(FName NewName) override;`
- L46 _public prototype_ `virtual int32 RenameNotify(const FName NewName, const FName OldName, bool bRenameInAnimations = true) override;`
- L47 _public prototype_ `virtual int32 RenameSyncMarker(const FName NewName, const FName OldName, bool bRenameInAnimations = true) override;`
- L48 _public prototype_ `virtual void BroadcastNotifyChanged() override;`
- L49 _public prototype_ `virtual void GetCompatibleAnimSequences(TArray<struct FAssetData>& OutAssets) override;`
- L50 _public prototype_ `virtual void RenameSocket(const FName OldSocketName, const FName NewSocketName, USkeletalMesh* InSkeletalMesh) override;`
- L51 _public prototype_ `virtual void SetSocketParent(const FName& SocketName, const FName& NewParentName, USkeletalMesh* InSkeletalMesh, bool bKeepAbsoluteLocation) override;`
- L52 _public prototype_ `virtual bool DoesSocketAlreadyExist(const class USkeletalMeshSocket* InSocket, const FText& InSocketName, ESocketParentType SocketParentType, USkeletalMesh* InSkeletalMesh) const override;`
- L53 _public prototype_ `virtual bool DoesVirtualBoneAlreadyExist(const FString& InVBName) const override;`
- L54 _public prototype_ `virtual void RenameVirtualBone(const FName OriginalName, const FName InVBName) override;`
- L55 _public prototype_ `virtual void SetPreviewMesh(class USkeletalMesh* InSkeletalMesh) override;`
- L56 _public prototype_ `virtual void LoadAdditionalPreviewSkeletalMeshes() override;`
- L57 _public prototype_ `virtual void SetAdditionalPreviewSkeletalMeshes(class UDataAsset* InPreviewCollectionAsset) override;`
- L58 _public prototype_ `virtual void RenameRetargetSource(const FName InOldName, const FName InNewName) override;`
- L59 _public prototype_ `virtual void AddRetargetSource(const FName& InName, USkeletalMesh* InReferenceMesh) override;`
- L60 _public prototype_ `virtual void DeleteRetargetSources(const TArray<FName>& InRetargetSourceNames) override;`
- L61 _public prototype_ `virtual void RefreshRetargetSources(const TArray<FName>& InRetargetSourceNames) override;`
- L62 _public prototype_ `virtual void AddCompatibleSkeleton(const USkeleton* InCompatibleSkeleton) override;`
- L63 _public prototype_ `virtual void RemoveCompatibleSkeleton(const USkeleton* InCompatibleSkeleton) override;`
- L64 _public prototype_ `virtual void RemoveUnusedBones() override;`
- L65 _public prototype_ `virtual void FindUnusedBones(TArray<FName>& OutUnusedBones, bool bSilent = false) override;`
- L66 _public prototype_ `virtual void UpdateSkeletonReferencePose(USkeletalMesh* InSkeletalMesh) override;`
- L67 _public prototype_ `virtual void RegisterSlotNode(const FName& InSlotName) override;`
- L68 _public prototype_ `virtual bool AddSlotGroupName(const FName& InSlotName) override;`
- L69 _public prototype_ `virtual void SetSlotGroupName(const FName& InSlotName, const FName& InGroupName) override;`
- L70 _public prototype_ `virtual void DeleteSlotName(const FName& InSlotName) override;`
- L71 _public prototype_ `virtual void DeleteSlotGroup(const FName& InGroupName) override;`
- L72 _public prototype_ `virtual void RenameSlotName(const FName InOldSlotName, const FName InNewSlotName) override;`
- L73 _public prototype_ `virtual void RegisterOnNotifiesChanged(const FSimpleMulticastDelegate::FDelegate& InDelegate) override;`
- L74 _public prototype_ `virtual void UnregisterOnNotifiesChanged(FDelegateUserObject Thing) override;`
- L75 _public prototype_ `virtual FDelegateHandle RegisterOnSlotsChanged(const FSimpleMulticastDelegate::FDelegate& InOnSlotsChanged) override;`
- L76 _public prototype_ `virtual void UnregisterOnSlotsChanged(FDelegateHandle InHandle) override;`
- L77 _public prototype_ `virtual void SetBoneTranslationRetargetingMode(FName InBoneName, EBoneTranslationRetargetingMode::Type NewRetargetingMode) override;`
- L78 _public prototype_ `virtual EBoneTranslationRetargetingMode::Type GetBoneTranslationRetargetingMode(FName InBoneName) const override;`
- L79 _public prototype_ `virtual void RefreshBoneTree() override;`
- L80 _public prototype_ `virtual USkeletalMeshSocket* AddSocket(const FName& InBoneName) override;`
- L83 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L84 _public function_ `virtual FString GetReferencerName() const override`
- L90 _public prototype_ `FName GenerateUniqueSocketName(FName InName, USkeletalMesh* InSkeletalMesh);` — Generates a unique socket name from the input name, by changing the FName's number
- L93 _public prototype_ `void HandlePasteSockets(const FName& InBoneName, USkeletalMesh* InSkeletalMesh);` — Handle the user pasting sockets
- L96 _public prototype_ `USkeletalMeshSocket* HandleAddSocket(const FName& InBoneName);` — Handles adding a socket to the specified bone (i.e. skeleton, not mesh)
- L99 _public prototype_ `bool HandleAddVirtualBone(const FName SourceBoneName, const FName TargetBoneName);` — Handle adding a new virtual bone to the skeleton
- L102 _public prototype_ `bool HandleAddVirtualBone(const FName SourceBoneName, const FName TargetBoneName, FName& NewVirtualBoneName);` — Handle adding a new virtual bone to the skeleton
- L105 _public prototype_ `void HandleCustomizeSocket(USkeletalMeshSocket* InSocketToCustomize, USkeletalMesh* InSkeletalMesh);` — Function to customize a socket - this essentially copies a socket from the skeleton to the mesh
- L108 _public prototype_ `void HandlePromoteSocket(USkeletalMeshSocket* InSocketToPromote);` — Function to promote a socket - this essentially copies a socket from the mesh to the skeleton
- L111 _public prototype_ `void HandleRemoveAllAssets(TSharedPtr<class IPersonaPreviewScene> InPreviewScene);` — Handle removing all attached assets, optionally keeping a preview scene in sync
- L114 _public prototype_ `void HandleAttachAssets(const TArray<UObject*>& InObjects, const FName& InAttachToName, bool bAttachToMesh, TSharedPtr<class IPersonaPreviewScene> InPreviewScene);` — Handle attaching assets to the skeleton or mesh, optionally keeping a preview scene in sync
- L117 _public prototype_ `void HandleDeleteAttachedAssets(const TArray<FPreviewAttachedObjectPair>& InAttachedObjects, TSharedPtr<class IPersonaPreviewScene> InPreviewScene);` — Handle deleting attached assets, optionally keeping a preview scene in sync
- L120 _public prototype_ `void HandleDeleteSockets(const TArray<FSelectedSocketInfo>& InSocketInfo, TSharedPtr<class IPersonaPreviewScene> InPreviewScene);` — Handle deleting sockets, optionally keeping a preview scene in sync
- L123 _public prototype_ `void HandleDeleteVirtualBones(const TArray<FName>& InVirtualBoneInfo, TSharedPtr<class IPersonaPreviewScene> InPreviewScene);` — Handle deleting virtual bones, optionally keeping a preview scene in sync
- L126 _public prototype_ `void SetBoneTranslationRetargetingModeRecursive(const TArray<FName>& InBoneNames, EBoneTranslationRetargetingMode::Type NewRetargetingMode);` — Set Bone Translation Retargeting Mode for the passed-in bones and their children.
- L129 _public prototype_ `void RecursiveSetBlendProfileScales(const FName& InBlendProfileName, const TArray<FName>& InBoneNames, float InScaleToSet);` — Sets the blend scale for the selected bones and all of their children
- L132 _public prototype_ `TSharedRef<class ISkeletonTree> CreateSkeletonTree(const struct FSkeletonTreeArgs& InSkeletonTreeArgs);` — Create a new skeleton tree to edit this editable skeleton
- L135 _public prototype_ `TSharedRef<class SWidget> CreateBlendProfilePicker(const struct FBlendProfilePickerArgs& InArgs);` — Create a new blend profile picker to edit this editable skeleton's blend profiles
- L138 _public function_ `bool IsEdited() const` — Check whether we have any widgets editing our data
- L141 _public prototype_ `void RegisterOnSkeletonHierarchyChanged(const USkeleton::FOnSkeletonHierarchyChanged& InDelegate);` — Register for skeleton changes
- L144 _public prototype_ `void UnregisterOnSkeletonHierarchyChanged(FDelegateUserObject Thing);` — Unregister for skeleton changes
- L147 _public prototype_ `void RecreateBoneTree(USkeletalMesh* NewPreviewMesh);` — Wrap USkeleton::RecreateBoneTree
- L151 _private prototype_ `void DeleteAttachedObjects(FPreviewAssetAttachContainer& AttachedAssets, TSharedPtr<class IPersonaPreviewScene> InPreviewScene);` — Helper function for deleting attached objects
- L154 _private prototype_ `void GetAssetsContainingCurves(const FName& InContainerName, const TArray<FName>& InNames, TArray<FAssetData>& OutAssets) const;` — Helper function for finding animations that use certain curves
- L158 _private member_ `TObjectPtr<class USkeleton> Skeleton;` — The skeleton we are editing
- L161 _private member_ `TArray<TWeakPtr<class SSkeletonTree>> SkeletonTrees;` — All skeleton tree widgets that are editing this skeleton
- L164 _private member_ `TArray<TWeakPtr<class SBlendProfilePicker>> BlendProfilePickers;` — All blend profile widgets that are editing this skeleton
- L167 _private member_ `FSimpleMulticastDelegate OnTreeRefresh;` — Delegate called when trees need refreshing
- L170 _private member_ `FSimpleMulticastDelegate OnNotifiesChanged;` — Delegate called when notifies are modified
- L173 _private member_ `FSimpleMulticastDelegate OnSlotsChanged;` — Delegate called when slots are modified

### `Source/Editor/SkeletonEditor/Private/SBlendProfilePicker.h` (Private)


#### class `SBlendProfilePicker`  
`class SBlendProfilePicker : public SCompoundWidget, public FEditorUndoClient`  
_L17-103_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Picker for UBlendProfile instances inside a USkeleton
- L20 _public function_ `SLATE_BEGIN_ARGS(SBlendProfilePicker) : _InitialProfile(nullptr) , _OnBlendProfileSelected() , _SupportedBlendProfileModes(EBlendProfilePickerMode::AllModes) , _AllowNew(true) , _AllowClear(true) , _AllowModify(true) , _Standalone(false)`
- L30 _public prototype_ `SLATE_ARGUMENT(UBlendProfile*, InitialProfile)` — Initial blend profile selected
- L49 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<class IEditableSkeleton> InEditableSkeleton);`
- L55 _public prototype_ `void SetSelectedProfile(UBlendProfile* InProfile, bool bBroadcast = true);` — Set the selected profile externally @param InProfile New Profile to set @param bBroadcast Whether or not to broadcast this selection
- L58 _public prototype_ `UBlendProfile* const GetSelectedBlendProfile() const;` — Get the currently selected blend profile
- L61 _public prototype_ `FName GetSelectedBlendProfileName() const;` — Get the currently selected blend profile name
- L64 _public prototype_ `void OnCreateNewProfileComitted(const FText& NewName, ETextCommit::Type CommitType, EBlendProfileMode InMode);` — Create a New Blend profile withe the provided profile name and mode
- L67 _public prototype_ `void OnClearSelection();` — Deselect the current blend profile
- L72 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L73 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L75 _private prototype_ `void OnCreateNewProfile(EBlendProfileMode InMode);`
- L77 _private prototype_ `void OnProfileSelected(FName InBlendProfileName);`
- L78 _private prototype_ `void OnProfileRemoved(FName InBlendProfileName);`
- L79 _private prototype_ `void OnProfileModeChanged(EBlendProfileMode ProfileMode, FName InBlendProfileName);`
- L81 _private prototype_ `FText GetSelectedProfileName() const;`
- L83 _private prototype_ `TSharedRef<SWidget> GetMenuContent();`
- L85 _private member_ `bool bShowNewOption;`
- L86 _private member_ `bool bShowClearOption;`
- L87 _private member_ `bool bIsStandalone;`
- L88 _private member_ `bool bAllowModify;`
- L89 _private member_ `bool bAllowBlendMask;`
- L90 _private member_ `bool bAllowOnlyBlendMask;`
- L93 _private member_ `EBlendProfilePickerMode SupportedBlendProfileModes;` — Only display Blend Profiles w/ specified Blend Profile modes (EBlendProfilePickerMode values are flags.)
- L95 _private member_ `FName SelectedProfileName;`
- L97 _private member_ `TSharedPtr<class IEditableSkeleton> EditableSkeleton;`
- L99 _private member_ `TSharedPtr<class IPropertyHandle> PropertyHandle;`
- L101 _private member_ `FOnBlendProfileSelected BlendProfileSelectedDelegate;`

### `Source/Editor/SkeletonEditor/Private/SSkeletonTree.h` (Private)


#### class `SSkeletonTree`  
`class SSkeletonTree : public ISkeletonTree, public FSelfRegisteringEditorUndoClient`  
_L52-482_
- inherits: `ISkeletonTree,FSelfRegisteringEditorUndoClient`
- L55 _public function_ `SLATE_BEGIN_ARGS( SSkeletonTree ) : _IsEditable(true)`
- L65 _public function_ `SSkeletonTree() : bSelecting(false)`
- L69 _public prototype_ `~SSkeletonTree();`
- L71 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FEditableSkeleton>& InEditableSkeleton, const FSkeletonTreeArgs& InSkeletonTreeArgs);`
- L74 _public prototype_ `virtual void Refresh() override;` — ISkeletonTree interface
- L75 _public prototype_ `virtual void RefreshFilter() override;`
- L76 _public function_ `virtual TSharedRef<class IEditableSkeleton> GetEditableSkeleton() const override`
- L77 _public function_ `virtual TSharedPtr<class IPersonaPreviewScene> GetPreviewScene() const override`
- L78 _public prototype_ `virtual void SetSkeletalMesh(USkeletalMesh* NewSkeletalMesh) override;`
- L79 _public prototype_ `virtual void SetSelectedSocket(const struct FSelectedSocketInfo& InSocketInfo) override;`
- L80 _public prototype_ `virtual void SetSelectedBone(const FName& InBoneName, ESelectInfo::Type InSelectInfo) override;`
- L81 _public prototype_ `virtual void SetSelectedBones(const TArray<FName>& InBoneNames, ESelectInfo::Type InSelectInfo) override;`
- L82 _public prototype_ `virtual void DeselectAll() override;`
- L83 _public prototype_ `virtual TArray<TSharedPtr<ISkeletonTreeItem>> GetSelectedItems() const override;`
- L84 _public prototype_ `virtual void SelectItemsBy(TFunctionRef<bool(const TSharedRef<ISkeletonTreeItem>&, bool&)> Predicate, const ESelectInfo::Type SelectInfo) const override;`
- L85 _public prototype_ `virtual void DuplicateAndSelectSocket(const FSelectedSocketInfo& SocketInfoToDuplicate, const FName& NewParentBoneName = FName()) override;`
- L86 _public prototype_ `virtual void ResetBoneTransforms(const bool bSelectedOnly) override;`
- L88 _public function_ `virtual FDelegateHandle RegisterOnSelectionChanged(const FOnSkeletonTreeSelectionChanged& Delegate) override`
- L93 _public function_ `virtual void UnregisterOnSelectionChanged(FDelegateHandle DelegateHandle) override`
- L98 _public prototype_ `virtual UBlendProfile* GetSelectedBlendProfile() override;`
- L99 _public prototype_ `virtual void AttachAssets(const TSharedRef<ISkeletonTreeItem>& TargetItem, const TArray<FAssetData>& AssetData) override;`
- L100 _public function_ `virtual TSharedPtr<SWidget> GetSearchWidget() const override`
- L101 _public function_ `virtual TSharedPtr<IPinnedCommandList> GetPinnedCommandList() const override`
- L103 _public function_ `bool ShouldAllowSkeletonOperations() const`
- L104 _public function_ `bool ShouldAllowMeshOperations() const`
- L107 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FSelfRegisteringEditorUndoClient interface
- L108 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L111 _public prototype_ `void CreateTreeColumns();` — Creates the tree control and then populates
- L114 _public prototype_ `void CreateFromSkeleton();` — Function to build the skeleton tree widgets from the source skeleton tree
- L117 _public prototype_ `void ApplyFilter();` — Apply filtering to the tree
- L120 _public prototype_ `void SetInitialExpansionState();` — Set the initial expansion state of the tree items
- L123 _public prototype_ `void NotifyUser( FNotificationInfo& NotificationInfo );` — Utility function to print notifications to the user
- L126 _public prototype_ `void OnItemScrolledIntoView( TSharedPtr<ISkeletonTreeItem> InItem, const TSharedPtr<ITableRow>& InWidget);` — Callback when an item is scrolled into view, handling calls to rename items
- L129 _public prototype_ `void OnTreeDoubleClick( TSharedPtr<ISkeletonTreeItem> InItem );` — Callback for when the user double-clicks on an item in the tree
- L132 _public prototype_ `void SetTreeItemExpansionRecursive(TSharedPtr< ISkeletonTreeItem > TreeItem, bool bInExpansionState) const;` — Handle recursive expansion/contraction of the tree
- L135 _public prototype_ `void SetBoneTranslationRetargetingModeRecursive(EBoneTranslationRetargetingMode::Type NewRetargetingMode);` — Set Bone Translation Retargeting Mode for bone selection, and their children.
- L143 _public prototype_ `void RemoveFromLOD(int32 LODIndex, EBoneReductionSelectionMode SelectionMode, bool bIncludeBelowLODs);`
- L147 _public function_ `inline void RemoveFromLOD(int32 LODIndex, bool bIncludeSelected, bool bIncludeBelowLODs)` — `UE_DEPRECATED(5.8, "RemoveFromLOD(int32, bool, bool) is deprecated. Use RemoveFromLOD(int32, bool, ERemoveFromLODMode).")` — Remove the selected bones from LOD of LODIndex when using simplygon
- L154 _public prototype_ `void OnLODSwitched();` — Called when the preview mesh is changed - simply rebuilds the skeleton tree for the new mesh
- L157 _public prototype_ `void OnPreviewMeshChanged(USkeletalMesh* InOldSkeletalMesh, USkeletalMesh* InNewSkeletalMesh);` — Called when the preview mesh is changed
- L160 _public prototype_ `FName GetSelectedBlendProfileName() const;` — Get the name of the currently selected blend profile
- L163 _public prototype_ `void HandleTreeRefresh();` — Delegate handler for when the tree needs refreshing
- L166 _public function_ `TSharedRef<FEditableSkeleton> GetEditableSkeletonInternal() const` — Get a shared reference to the skeleton tree that owns us
- L169 _public prototype_ `void PostRenameSocket(UObject* InAttachedObject, const FName& InOldName, const FName& InNewName);` — Update preview scene and tree after a socket rename
- L172 _public prototype_ `void PostDuplicateSocket(UObject* InAttachedObject, const FName& InSocketName);` — Update preview scene and tree after a socket duplication
- L175 _public prototype_ `void PostSetSocketParent();` — Update tree after a socket changes parent
- L179 _private prototype_ `void BindCommands();` — Binds the commands in FSkeletonTreeCommands to functions in this class
- L182 _private prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(TSharedPtr<ISkeletonTreeItem> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info
- L185 _private prototype_ `void GetFilteredChildren(TSharedPtr<ISkeletonTreeItem> InInfo, TArray< TSharedPtr<ISkeletonTreeItem> >& OutChildren);` — Get all children for a given entry in the list
- L188 _private prototype_ `TSharedPtr< SWidget > CreateContextMenu();` — Called to display context menu when right clicking on the widget
- L191 _private prototype_ `TSharedRef< SWidget > CreateNewMenuWidget();` — Called to display the add new menu
- L194 _private prototype_ `void RegisterNewMenu();` — Called to create the add new menu
- L197 _private prototype_ `TSharedRef< SWidget > CreateFilterMenuWidget();` — Called to display the filter menu
- L200 _private prototype_ `void RegisterFilterMenu();` — Called to create the filter menu
- L203 _private prototype_ `void OnCopyBoneNames();` — Function to copy selected bone name to the clipboard
- L206 _private prototype_ `void OnResetBoneTransforms(const bool bSelectedOnly = true);` — Function to reset the transforms of selected bones
- L209 _private prototype_ `void OnCopySockets() const;` — Function to copy selected sockets to the clipboard
- L212 _private prototype_ `bool CanCopySockets() const;` — Whether we can copy sockets
- L215 _private prototype_ `FString SerializeSocketToString( class USkeletalMeshSocket* Socket, ESocketParentType ParentType ) const;` — Function to serialize a single socket to a string
- L218 _private prototype_ `void OnPasteSockets(bool bPasteToSelectedBone);` — Function to paste selected sockets from the clipboard
- L221 _private prototype_ `bool CanPasteSockets() const;` — Whether we can paste sockets
- L224 _private prototype_ `void OnAddSocket();` — Function to add a socket to the selected bone (skeleton, not mesh)
- L227 _private prototype_ `bool CanRenameSelected() const;` — Function to check if it is possible to rename the selected item
- L230 _private prototype_ `void OnRenameSelected();` — Function to start renaming the selected item
- L233 _private prototype_ `void OnCustomizeSocket();` — Function to customize a socket - this essentially copies a socket from the skeleton to the mesh
- L236 _private prototype_ `void OnPromoteSocket();` — Function to promote a socket - this essentially copies a socket from the mesh to the skeleton
- L239 _private prototype_ `static TSharedRef<class SBoneTreeMenu> CreateVirtualBoneMenu(SSkeletonTree* InSkeletonTree);` — Create sub menu to allow users to pick a target bone for the new space switching bone(s)
- L242 _private prototype_ `void OnVirtualTargetBonePicked(FName TargetBoneName, TArray<TSharedPtr<class ISkeletonTreeItem>> SourceBones);` — Handler for user picking a target bone
- L245 _private prototype_ `void FillAttachAssetSubmenu(FMenuBuilder& MenuBuilder, const TSharedPtr<class ISkeletonTreeItem> TargetItem);` — Create content picker sub menu to allow users to pick an asset to attach
- L248 _private prototype_ `void OnAssetSelectedFromPicker(const FAssetData& AssetData, const TSharedPtr<class ISkeletonTreeItem> TargetItem);` — Helper function for asset picker that handles users choice
- L251 _private prototype_ `void OnRemoveAllAssets();` — Context menu function to remove all attached assets
- L254 _private prototype_ `bool CanRemoveAllAssets() const;` — Context menu function to control enabled/disabled status of remove all assets menu item
- L257 _private function_ `void OnCopySocketToMesh()` — Functions to copy sockets from the skeleton to the mesh
- L260 _private prototype_ `bool OnIsSelectableOrNavigable(TSharedPtr<class ISkeletonTreeItem> InItem) const;` — Callback function to be called when selection changes to check if the next item is selectable or navigable.
- L263 _private prototype_ `void OnSelectionChanged(TSharedPtr<class ISkeletonTreeItem> Selection, ESelectInfo::Type SelectInfo);` — Callback function to be called when selection changes in the tree view widget.
- L266 _private prototype_ `void OnFilterTextChanged( const FText& SearchText );` — Filters the SListView when the user changes the search text box (NameFilterBox)
- L269 _private prototype_ `void SetBoneFilter(EBoneFilter InBoneFilter );` — Sets which types of bone to show
- L272 _private prototype_ `bool IsBoneFilter(EBoneFilter InBoneFilter ) const;` — Queries the bone filter
- L275 _private prototype_ `void SetSocketFilter(ESocketFilter InSocketFilter );` — Sets which types of socket to show
- L278 _private prototype_ `bool IsSocketFilter(ESocketFilter InSocketFilter ) const;` — Queries the bone filter
- L281 _private prototype_ `FText GetFilterMenuTooltip() const;` — Returns the current text for the filter button tooltip - "All", "Mesh" or "Weighted" etc.
- L284 _private prototype_ `bool IsAddingSocketsAllowed() const;` — We can only add sockets in Active, Skeleton or All mode (otherwise they just disappear)
- L287 _private prototype_ `bool IsShowingAdvancedOptions() const;` — Handler for "Show Retargeting Options" check box IsChecked functionality
- L290 _private prototype_ `void OnChangeShowingAdvancedOptions();` — Handler for when we change the "Show Retargeting Options" check box
- L293 _private prototype_ `bool IsShowingDebugVisualizationOptions() const;` — Handler for "Show Debug Visualization Options" check box IsChecked functionality
- L296 _private prototype_ `void OnChangeShowingDebugVisualizationOptions();` — Handler for when we change the "Show Debug Visualization Options" check box
- L299 _private prototype_ `void SetPreviewComponentSocketFilter() const;` — This replicates the socket filter to the previewcomponent so that the viewport can use the same settings
- L302 _private prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent );` — Override OnKeyDown
- L305 _private prototype_ `bool CanDeleteSelectedRows() const;` — Check whether we can delete all the selected sockets/assets
- L308 _private prototype_ `void OnDeleteSelectedRows();` — Function to delete all the selected sockets/assets
- L311 _private prototype_ `void DeleteAttachedAssets(const TArray<TSharedPtr<class FSkeletonTreeAttachedAssetItem>>& InDisplayedAttachedAssetInfos );` — Function to remove attached assets from the skeleton/mesh
- L314 _private prototype_ `void DeleteSockets(const TArray<TSharedPtr<class FSkeletonTreeSocketItem>>& InDisplayedSocketInfos );` — Function to remove sockets from the skeleton/mesh
- L317 _private prototype_ `void DeleteVirtualBones(const TArray<TSharedPtr<class FSkeletonTreeVirtualBoneItem>>& InDisplayedVirtualBonestInfos);` — Function to remove virtual bones from the skeleton/mesh
- L320 _private prototype_ `void OnBlendProfileSelected(UBlendProfile* NewProfile);` — Called when the user selects a blend profile to edit
- L323 _private prototype_ `void RecursiveSetBlendProfileScales(float InScaleToSet);` — Sets the blend scale for the selected bones and all of their children
- L326 _private prototype_ `static void CreateMenuForBoneReduction(FMenuBuilder& MenuBuilder, SSkeletonTree* SkeletonTree, int32 LODIndex, bool bIncludeSelected);` — Submenu creator handler for the given skeleton
- L329 _private prototype_ `void HandleFocusCamera();` — Handle focusing the camera on the current selection
- L332 _private prototype_ `void HandleFrameSelection();` — Handle framing the selected item in the tree
- L335 _private prototype_ `ESkeletonTreeFilterResult HandleFilterSkeletonTreeItem(const FSkeletonTreeFilterArgs& InArgs, const TSharedPtr<class ISkeletonTreeItem>& InItem);` — Handle filtering the tree
- L338 _private function_ `const FReferenceSkeleton& OnGetReferenceSkeleton() const` — Called when bone tree queries reference skeleton
- L344 _private prototype_ `void HandleSelectedBoneChanged(const FName& InBoneName, ESelectInfo::Type InSelectInfo);` — Handle bone selection changing externally
- L345 _private prototype_ `void HandleSelectedBonesChanged(const TArray<FName>& InBoneNames, ESelectInfo::Type InSelectInfo);`
- L348 _private prototype_ `void HandleSelectedSocketChanged(const FSelectedSocketInfo& InSocketInfo);` — Handle socket selection changing externally
- L351 _private prototype_ `void HandleDeselectAll();` — Handle external deselection event
- L354 _private prototype_ `void HandlePackageReloaded(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);` — Handle package reloading (might be our skeleton)
- L357 _private prototype_ `void OnCreateBlendProfile(const EBlendProfileMode InMode);` — Creates a new Blend Profile
- L360 _private prototype_ `void OnDeleteCurrentBlendProfile();` — Removes the active Blend Profile
- L363 _private prototype_ `void OnRenameBlendProfile();` — Removes the active Blend Profile
- L366 _private prototype_ `void RegisterBlendProfileMenu();` — Register Blend Profile Menu
- L369 _private prototype_ `static void CreateBlendProfileMenu(UToolMenu* InMenu);` — Create Blend Profile Menu
- L371 _private prototype_ `TSharedRef<SWidget> GetBlendProfileColumnMenuContent();`
- L373 _private prototype_ `void ExpandTreeOnSelection(TSharedPtr<ISkeletonTreeItem> RowToExpand, bool bForce = false);`
- L377 _private member_ `TWeakPtr<FEditableSkeleton> EditableSkeleton;` — Pointer back to the skeleton tree that owns us
- L380 _private member_ `TWeakPtr<IPersonaPreviewScene> PreviewScene;` — Link to a preview scene
- L383 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — SSearchBox to filter the tree
- L386 _private member_ `TSharedPtr<SBlendProfilePicker> BlendProfilePicker;` — The blend profile picker displaying the selected profile
- L389 _private member_ `TSharedPtr<SInlineEditableTextBlock> BlendProfileHeader;` — Blend Profile Header Label.  Also used to name new blend profiles
- L392 _private member_ `TSharedPtr<SOverlay> TreeHolder;` — Widget user to hold the skeleton tree
- L395 _private member_ `TSharedPtr<SSkeletonTreeView<TSharedPtr<class ISkeletonTreeItem>>> SkeletonTreeView;` — Widget used to display the skeleton hierarchy
- L398 _private member_ `TArray<TSharedPtr<class ISkeletonTreeItem>> Items;` — A tree of unfiltered items
- L401 _private member_ `TArray<TSharedPtr<class ISkeletonTreeItem>> LinearItems;` — A "mirror" of the tree as a flat array for easier searching
- L404 _private member_ `TArray<TSharedPtr<class ISkeletonTreeItem>> FilteredItems;` — Filtered view of the skeleton tree. This is what is actually used in the tree widget
- L407 _private member_ `TAttribute<bool> IsEditable;` — Is this view editable
- L410 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L413 _private member_ `TSharedPtr<FUICommandList_Pinnable> UICommandList;` — Commands that are bound to delegates
- L416 _private member_ `EBlendProfileMode NewBlendProfileMode;` — Current type of blend profile no create. We shouldn't need to hold state for this, but blend profile creation is tied to its header text committed
- L419 _private member_ `bool bIsCreateNewBlendProfile = false;` — Whether we are creating or renaming a BlendProfile, so the EditBox know what to do
- L422 _private member_ `EBoneFilter BoneFilter;` — Current type of bones to show
- L425 _private member_ `ESocketFilter SocketFilter;` — Current type of sockets to show
- L428 _private member_ `TSharedPtr<ISkeletonTreeItem> DeferredRenameRequest;` — Points to an item that is being requested to be renamed
- L431 _private member_ `int32 LastCachedLODForPreviewMeshComponent;` — Last Cached Preview Mesh Component LOD
- L434 _private member_ `FOnSkeletonTreeSelectionChangedMulticast OnSelectionChangedMulticast;` — Delegate for when an item is selected
- L437 _private member_ `bool bSelecting;` — Selection recursion guard flag
- L440 _private member_ `TSharedPtr<SComboButton> FilterComboButton;` — Hold onto the filter combo button to set its foreground color
- L443 _private prototype_ `void AddVirtualBones(const TArray<FVirtualBone>& VirtualBones);` — Add virtual bones to the skeleton tree
- L446 _private prototype_ `bool IsBlendProfileSelected(FName ProfileName) const;` — Checks if the named profile is the currently selected/active one
- L449 _private member_ `TSharedPtr<class ISkeletonTreeBuilder> Builder;` — The builder we use to construct the tree
- L452 _private member_ `TSharedPtr<class FTextFilterExpressionEvaluator> TextFilterPtr;` — Compiled filter search terms.
- L455 _private member_ `bool bAllowMeshOperations;` — Whether to allow operations that modify the mesh
- L458 _private member_ `bool bAllowSkeletonOperations;` — Whether to allow operations that modify the mesh
- L461 _private member_ `bool bShowDebugVisualizationOptions;` — Whether to show the filter option to allow filtering of debug draw elements in the viewport.
- L464 _private member_ `bool bAllowInvisibleItemSelection = false;` — Wether children can remain selected while their parent is collapsed in the tree
- L467 _private member_ `TSharedPtr<FExtender> Extenders;` — Extenders for menus
- L470 _private member_ `FOnGetFilterText OnGetFilterText;` — Delegate that allows custom filtering text to be shown on the filter button
- L473 _private member_ `ESkeletonTreeMode Mode;` — The mode that this skeleton tree is in
- L476 _private member_ `TSharedPtr<IPinnedCommandList> PinnedCommands;` — Pinned commands panel
- L479 _private member_ `FName ContextName;` — Context name used to persist settings

#### enum `SSkeletonTree::EBoneReductionSelectionMode`  
`enum class EBoneReductionSelectionMode : uint8`  
_L137-142_
- L139 _public enumerator_ `SelectedBones`
- L140 _public enumerator_ `ChildrenOfSelectedBones`
- L141 _public enumerator_ `AllUnusedBones`

### `Source/Editor/SkeletonEditor/Private/SSkeletonTreeRow.h` (Private)


#### class `SSkeletonTreeRow`  
`class SSkeletonTreeRow : public SMultiColumnTableRow<TSharedPtr<ISkeletonTreeItem>>`  
_L30-96_
- inherits: `SMultiColumnTableRow<TSharedPtr<ISkeletonTreeItem>>`
- L34 _public function_ `SLATE_BEGIN_ARGS(SSkeletonTreeRow)`
- L37 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<ISkeletonTreeItem>, Item) SLATE_ATTRIBUTE(FText, FilterText);` — The item for this row
- L43 _public prototype_ `SLATE_EVENT(FOnDraggingTreeItem, OnDraggingItem);` — Delegate for dragging items
- L45 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L50 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L53 _public prototype_ `virtual void ConstructChildren(ETableViewMode::Type InOwnerTableMode, const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent) override;` — Overridden from STableRow. Allows us to generate inline edit widgets.
- L56 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — Override OnDragEnter for drag and drop of sockets onto bones
- L59 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;` — Override OnDragLeave for drag and drop of sockets onto bones
- L62 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — Override OnDrop for drag and drop of sockets and meshes onto bones
- L65 _public prototype_ `virtual int32 DoesItemHaveChildren() const override;` — Override DoesItemHaveChildren to add expander to in-line editors
- L68 _public prototype_ `virtual bool IsItemExpanded() const override;` — @return true if the corresponding item is expanded; false otherwise
- L71 _public prototype_ `virtual void ToggleExpansion() override;` — Toggle the expansion of the item associated with this row
- L76 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Handler for starting a drag/drop action
- L79 _protected function_ `TSharedRef<class IEditableSkeleton> GetEditableSkeleton() const` — Get the editable skeleton we are editing
- L82 _protected function_ `TSharedRef<class ISkeletonTree> GetSkeletonTree() const` — Get the skeleton tree we are embedded in
- L86 _private member_ `TWeakPtr<ISkeletonTreeItem> Item;` — The item this row is holding
- L89 _private member_ `TAttribute<FText> FilterText;` — Text the user typed into the search box - used for text highlighting
- L92 _private member_ `FOnDraggingTreeItem OnDraggingItem;` — Item that we're dragging
- L95 _private member_ `bool bIsAltDrag;` — Was the user pressing "Alt" when the drag was started?

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnDraggingTreeItem, const FGeometry&, const FPointerEvent&);`
- L28 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnDraggingTreeItem, const FGeometry&, const FPointerEvent&);`

### `Source/Editor/SkeletonEditor/Private/SkeletonEditor.h` (Private)


#### class `FSkeletonEditor`  
`class FSkeletonEditor : public ISkeletonEditor, public FEditorUndoClient, public FTickableEditorObject`  
_L46-165_
- inherits: `ISkeletonEditor,FEditorUndoClient,FTickableEditorObject`
- L49 _public prototype_ `FSkeletonEditor();`
- L51 _public prototype_ `virtual ~FSkeletonEditor();`
- L54 _public prototype_ `void InitSkeletonEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, class USkeleton* InSkeleton);` — Edits the specified Skeleton object
- L57 _public function_ `virtual TSharedRef<class IPersonaToolkit> GetPersonaToolkit() const override` — IHasPersonaToolkit interface
- L60 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — IToolkit interface
- L61 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L62 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L63 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L64 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L65 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L66 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L68 _public prototype_ `virtual IAnimationSequenceBrowser* GetAssetBrowser() const override;`
- L71 _public prototype_ `void HandleOpenNewAsset(UObject* InNewAsset);` — Handle opening a new asset from the asset browser
- L74 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L75 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L78 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject Interface
- L79 _public prototype_ `virtual TStatId GetStatId() const override;`
- L80 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L83 _public function_ `virtual FString GetDocumentationLink() const override` — @return the documentation location for this editor
- L89 _public function_ `TSharedRef<class ISkeletonTree> GetSkeletonTree() const` — Get the skeleton tree widget
- L91 _public prototype_ `UObject* HandleGetAsset();`
- L94 _public prototype_ `void HandleObjectsSelected(const TArray<UObject*>& InObjects);`
- L96 _public prototype_ `void HandleObjectSelected(UObject* InObject);`
- L98 _public prototype_ `void HandleSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo);`
- L100 _public prototype_ `void HandleDetailsCreated(const TSharedRef<class IDetailsView>& InDetailsView);`
- L102 _public prototype_ `void HandleAnimationSequenceBrowserCreated(const TSharedRef<class IAnimationSequenceBrowser>& InSequenceBrowser);`
- L104 _public prototype_ `void HandleViewportCreated(const TSharedRef<IPersonaViewport>& InViewport);`
- L107 _public prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget, int32 ZOrder = INDEX_NONE) override;` — FAssetEditorToolkit interface
- L108 _public prototype_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget) override;`
- L111 _private prototype_ `void ExtendMenu();`
- L113 _private prototype_ `void ExtendToolbar();`
- L115 _private prototype_ `void BindCommands();`
- L117 _private prototype_ `bool CanRemoveBones() const;`
- L119 _private prototype_ `void RemoveUnusedBones();`
- L121 _private prototype_ `void TestSkeletonCurveMetaDataForUse() const;`
- L123 _private prototype_ `void UpdateSkeletonRefPose();`
- L125 _private prototype_ `void OnAnimNotifyWindow();`
- L127 _private prototype_ `void OnRetargetManager();`
- L129 _private prototype_ `void OnImportAsset();`
- L131 _private prototype_ `void HandleOnPreviewSceneSettingsCustomized(IDetailLayoutBuilder& DetailBuilder);`
- L133 _private prototype_ `static TSharedPtr<FSkeletonEditor> GetSkeletonEditor(const FToolMenuContext& InMenuContext);`
- L136 _public member_ `FSimpleMulticastDelegate OnPostUndo;` — Multicast delegate fired on global undo/redo
- L139 _public member_ `FSimpleMulticastDelegate OnCurvesChanged;` — Multicast delegate fired on curves changing
- L143 _private member_ `USkeleton* Skeleton;` — The skeleton we are editing
- L146 _private member_ `TSharedPtr<FExtender> ToolbarExtender;` — Toolbar extender
- L149 _private member_ `TSharedPtr<FExtender> MenuExtender;` — Menu extender
- L152 _private member_ `TSharedPtr<class IPersonaToolkit> PersonaToolkit;` — Persona toolkit
- L155 _private member_ `TSharedPtr<class ISkeletonTree> SkeletonTree;` — Skeleton tree
- L158 _private member_ `TSharedPtr<class IPersonaViewport> Viewport;` — Viewport
- L161 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Details panel
- L164 _private member_ `TWeakPtr<class IAnimationSequenceBrowser> SequenceBrowser;` — Sequence Browser

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace SkeletonEditorModes`
- L27 _externvar_ `extern const FName SkeletonEditorMode;` (scope `SkeletonEditorModes`) — Mode identifiers
- L30 _namespace_ `namespace SkeletonEditorTabs`
- L33 _externvar_ `extern const FName DetailsTab;` (scope `SkeletonEditorTabs`) — Tab identifiers
- L34 _externvar_ `extern const FName SkeletonTreeTab;` (scope `SkeletonEditorTabs`)
- L35 _externvar_ `extern const FName ViewportTab;` (scope `SkeletonEditorTabs`)
- L36 _externvar_ `extern const FName AssetBrowserTab;` (scope `SkeletonEditorTabs`)
- L37 _externvar_ `extern const FName AnimNotifiesTab;` (scope `SkeletonEditorTabs`)
- L38 _externvar_ `extern const FName CurveMetadataTab;` (scope `SkeletonEditorTabs`)
- L39 _externvar_ `extern const FName CurveDebuggerTab;` (scope `SkeletonEditorTabs`)
- L40 _externvar_ `extern const FName AdvancedPreviewTab;` (scope `SkeletonEditorTabs`)
- L41 _externvar_ `extern const FName RetargetManagerTab;` (scope `SkeletonEditorTabs`)
- L42 _externvar_ `extern const FName SlotNamesTab;` (scope `SkeletonEditorTabs`)
- L43 _externvar_ `extern const FName FindReplaceTab;` (scope `SkeletonEditorTabs`)

### `Source/Editor/SkeletonEditor/Private/SkeletonEditorCommands.h` (Private)


#### class `FSkeletonEditorCommands`  
`class FSkeletonEditorCommands : public TCommands<FSkeletonEditorCommands>`  
_L15-43_
- inherits: `TCommands<FSkeletonEditorCommands>`
- L18 _public function_ `FSkeletonEditorCommands() : TCommands<FSkeletonEditorCommands>(TEXT("SkeletonEditor"), NSLOCTEXT("Contexts", "SkeletonEditor", "Skeleton Editor"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L23 _public prototype_ `virtual void RegisterCommands() override;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ChangeSkeletonPreviewMesh;` — skeleton menu options Command to allow users to set the skeletons preview mesh
- L31 _public member_ `TSharedPtr<FUICommandInfo> RemoveUnusedBones;` — Command to allow users to remove unused bones (not referenced by any skeletalmesh) from the skeleton
- L33 _public member_ `TSharedPtr<FUICommandInfo> TestSkeletonCurveMetaDataForUse;` — Command to allow users to look for unused curves (curves that exist in animations that do not drive any morph/materials
- L35 _public member_ `TSharedPtr<FUICommandInfo> AnimNotifyWindow;` — Command to show Anim Notify window
- L37 _public member_ `TSharedPtr<FUICommandInfo> Retargeting;` — Command to show retargeting tools
- L39 _public member_ `TSharedPtr<FUICommandInfo> ImportMesh;` — Import Mesh for this Skeleton
- L42 _public member_ `TSharedPtr<FUICommandInfo> UpdateSkeletonRefPose;` — Command to allow users to remove unused bones (not referenced by any skeletalmesh) from the skeleton

### `Source/Editor/SkeletonEditor/Private/SkeletonEditorMode.h` (Private)


#### class `FSkeletonEditorMode`  
`class FSkeletonEditorMode : public FApplicationMode`  
_L10-17_
- inherits: `FApplicationMode`
- L13 _public prototype_ `FSkeletonEditorMode(TSharedRef<class FWorkflowCentricApplication> InHostingApp, TSharedRef<class ISkeletonTree> InSkeletonTree);`
- L16 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface

### `Source/Editor/SkeletonEditor/Private/SkeletonTreeAttachedAssetItem.h` (Private)


#### class `FSkeletonTreeAttachedAssetItem`  
`class FSkeletonTreeAttachedAssetItem : public FSkeletonTreeItem`  
_L13-52_
- inherits: `FSkeletonTreeItem`
- L16 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreeAttachedAssetItem, FSkeletonTreeItem) FSkeletonTreeAttachedAssetItem(UObject* InAsset, const FName& InAttachedTo, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L21 _public prototype_ `virtual void GenerateWidgetForNameColumn(TSharedPtr< SHorizontalBox > Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;` — ISkeletonTreeItem interface
- L22 _public prototype_ `virtual TSharedRef< SWidget > GenerateWidgetForDataColumn(const FName& DataColumnName, FIsSelected InIsSelected) override;`
- L23 _public function_ `virtual FName GetRowItemName() const`
- L24 _public function_ `virtual FName GetAttachName() const`
- L25 _public prototype_ `virtual void OnItemDoubleClicked() override;`
- L28 _public function_ `const FName& GetParentName() const` — Returns the name of the socket/bone this asset is attached to
- L31 _public function_ `UObject* GetAsset() const` — Return the asset this info represents
- L35 _private prototype_ `ECheckBoxState IsAssetDisplayed() const;` — Accessor for SCheckBox
- L38 _private prototype_ `void OnToggleAssetDisplayed(ECheckBoxState InCheckboxState);` — Called when user toggles checkbox
- L41 _private prototype_ `const FSlateBrush* OnGetAssetDisplayedButtonImage() const;` — Called when we need to get the state-based-image to show for the asset displayed checkbox
- L45 _private member_ `const FName AttachedTo;` — The name of the socket/bone this asset is attached to
- L48 _private member_ `UObject* Asset;` — The attached asset that this tree item represents
- L51 _private member_ `TWeakObjectPtr<USceneComponent> AssetComponent;` — The component of the attached asset

### `Source/Editor/SkeletonEditor/Private/SkeletonTreeBoneItem.h` (Private)


#### class `FSkeletonTreeBoneItem`  
`class FSkeletonTreeBoneItem : public FSkeletonTreeItem, public FGCObject`  
_L21-124_
- inherits: `FSkeletonTreeItem,FGCObject`
- L24 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreeBoneItem, FSkeletonTreeItem) FSkeletonTreeBoneItem(const FName& InBoneName, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L29 _public prototype_ `virtual void GenerateWidgetForNameColumn(TSharedPtr< SHorizontalBox > Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;` — ISkeletonTreeItem interface
- L30 _public prototype_ `virtual TSharedRef< SWidget > GenerateWidgetForDataColumn(const FName& DataColumnName, FIsSelected InIsSelected) override;`
- L31 _public function_ `virtual FName GetRowItemName() const override`
- L32 _public prototype_ `virtual void HandleDragEnter(const FDragDropEvent& DragDropEvent) override;`
- L33 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L34 _public prototype_ `virtual FReply HandleDrop(const FDragDropEvent& DragDropEvent) override;`
- L35 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L36 _public function_ `virtual UObject* GetObject() const override`
- L39 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L40 _public function_ `virtual FString GetReferencerName() const override`
- L46 _public prototype_ `bool IsBoneWeighted(int32 MeshBoneIndex, UDebugSkelMeshComponent* PreviewComponent);` — Check to see if the specified bone is weighted in the specified component
- L49 _public prototype_ `bool IsBoneRequired(int32 MeshBoneIndex, UDebugSkelMeshComponent* PreviewComponent);` — Check to see if the specified bone is required in the specified component
- L52 _public prototype_ `void CacheLODChange(UDebugSkelMeshComponent* PreviewComponent);` — Cache to use Bold Font or not
- L55 _public prototype_ `void EnableBoneProxyTick(bool bEnable);` — Enable and disable the bone proxy ticking
- L59 _private prototype_ `FSlateFontInfo GetBoneTextFont() const;` — Gets the font for displaying bone text in the skeletal tree
- L62 _private prototype_ `FSlateColor GetBoneTextColor(FIsSelected InIsSelected) const;` — Get the text color based on bone part of skeleton or part of mesh
- L65 _private prototype_ `const FSlateBrush* GetLODIcon() const;` — Brush of the icon
- L68 _private prototype_ `FText GetBoneToolTip();` — Function that returns the current tooltip for this bone, depending on how it's used by the mesh
- L71 _private prototype_ `FSlateColor GetRetargetingComboButtonForegroundColor() const;` — Vary the color of the combo based on hover state
- L74 _private prototype_ `TSharedRef< SWidget > CreateBoneTranslationRetargetingModeMenu();` — Create menu for Bone Translation Retargeting Mode.
- L77 _private prototype_ `FText GetTranslationRetargetingModeMenuTitle() const;` — Get Title for Bone Translation Retargeting Mode menu.
- L80 _private prototype_ `void OnBlendSliderCommitted(float NewValue, ETextCommit::Type CommitType);` — Callback from a slider widget if the text entry is used
- L83 _private prototype_ `void OnBlendSliderChanged(float NewValue);` — Callback from a slider widget if the slider is used
- L86 _private prototype_ `void OnBeginBlendSliderMovement();` — Callback from a slider widget when the user begins sliding
- L89 _private prototype_ `void OnEndBlendSliderMovement(float NewValue);` — Callback from a slider widget when the user has finished sliding
- L92 _private prototype_ `void SetBoneTranslationRetargetingMode(EBoneTranslationRetargetingMode::Type NewRetargetingMode);` — Set Translation Retargeting Mode for this bone.
- L95 _private prototype_ `float GetBoneBlendProfileScale() const;` — Get the current Blend Scale for this bone
- L98 _private prototype_ `TOptional<float> GetBlendProfileMaxSliderValue() const;` — Get the max slider value supported by the selected blend profile's mode
- L101 _private prototype_ `TOptional<float> GetBlendProfileMinSliderValue() const;` — Get the min slider value supported by the selected blend profile's mode
- L104 _private prototype_ `EVisibility GetBoneBlendProfileVisibility() const;` — Used to hide the Bone Profile row widget if there is no current Blend Profile
- L108 _private member_ `TObjectPtr<UBoneProxy> BoneProxy;` — Bone proxy object
- L111 _private member_ `FName BoneName;` — The actual bone data that we create Slate widgets to display
- L114 _private member_ `bool bWeightedBone;` — Weighted bone
- L117 _private member_ `bool bRequiredBone;` — Required bone
- L120 _private member_ `TSharedPtr<SComboButton> RetargetingComboButton;` — Reference to the retargeting combo button
- L123 _private member_ `bool bBlendSliderStartedTransaction;` — True if the user is in a transaction when moving the blend profile slider

### `Source/Editor/SkeletonEditor/Private/SkeletonTreeCommands.h` (Private)


#### class `FSkeletonTreeCommands`  
`class FSkeletonTreeCommands : public TCommands<FSkeletonTreeCommands>`  
_L18-131_
- inherits: `TCommands<FSkeletonTreeCommands>`
- desc: Class containing commands for skeleton tree actions
- L21 _public function_ `FSkeletonTreeCommands() : TCommands<FSkeletonTreeCommands> ( TEXT("SkeletonTree"),`
- L34 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L37 _public member_ `TSharedPtr< FUICommandInfo > ShowAllBones;` — Show all bones in the tree
- L40 _public member_ `TSharedPtr< FUICommandInfo > ShowMeshBones;` — Show only bones that are present in the current mesh
- L43 _public member_ `TSharedPtr< FUICommandInfo > ShowLODBones;` — Show only bones that are present in the current LOD
- L46 _public member_ `TSharedPtr< FUICommandInfo > ShowWeightedBones;` — Show only bones that have weighted vertices
- L49 _public member_ `TSharedPtr< FUICommandInfo > HideBones;` — Hide all bones
- L52 _public member_ `TSharedPtr< FUICommandInfo > ShowRetargeting;` — Show retargeting options
- L55 _public member_ `TSharedPtr< FUICommandInfo > ShowDebugVisualization;` — Show debug visualization options
- L58 _public member_ `TSharedPtr< FUICommandInfo > FilteringFlattensHierarchy;` — Flatten hierarchy on filter
- L61 _public member_ `TSharedPtr< FUICommandInfo > HideParentsWhenFiltering;` — Hide parents on filter
- L64 _public member_ `TSharedPtr< FUICommandInfo > ShowBoneIndex;` — Show bone numbers
- L67 _public member_ `TSharedPtr< FUICommandInfo > AddSocket;` — Add a socket to the skeleton
- L70 _public member_ `TSharedPtr< FUICommandInfo > CreateMeshSocket;` — Customize a socket for a mesh
- L73 _public member_ `TSharedPtr< FUICommandInfo > RemoveMeshSocket;` — Remove customization for a socket (actually just deletes the mesh socket)
- L76 _public member_ `TSharedPtr< FUICommandInfo > PromoteSocketToSkeleton;` — Promotes a mesh-only socket to the skeleton
- L79 _public member_ `TSharedPtr< FUICommandInfo > DeleteSelectedRows;` — Delete selected rows (deletes any sockets or assets selected in the tree
- L82 _public member_ `TSharedPtr< FUICommandInfo > ShowActiveSockets;` — Show active sockets
- L85 _public member_ `TSharedPtr< FUICommandInfo > ShowMeshSockets;` — Show skeletal mesh sockets
- L88 _public member_ `TSharedPtr< FUICommandInfo > ShowSkeletonSockets;` — Show skeleton sockets
- L91 _public member_ `TSharedPtr< FUICommandInfo > ShowAllSockets;` — Show all sockets
- L94 _public member_ `TSharedPtr< FUICommandInfo > HideSockets;` — Hide all sockets
- L97 _public member_ `TSharedPtr< FUICommandInfo > CopyBoneNames;` — Copy bone names
- L100 _public member_ `TSharedPtr< FUICommandInfo > ResetBoneTransforms;` — Reset selected bones transforms
- L103 _public member_ `TSharedPtr< FUICommandInfo > ResetAllBonesTransforms;` — Reset all bones transforms
- L106 _public member_ `TSharedPtr< FUICommandInfo > CopySockets;` — Copy sockets to clipboard
- L109 _public member_ `TSharedPtr< FUICommandInfo > PasteSockets;` — Paste sockets from clipboard
- L112 _public member_ `TSharedPtr< FUICommandInfo > PasteSocketsToSelectedBone;` — Paste sockets from clipboard
- L115 _public member_ `TSharedPtr< FUICommandInfo > FocusCamera;` — Focus the camera on the current selection
- L118 _public member_ `TSharedPtr< FUICommandInfo > CreateTimeBlendProfile;` — Create a new blend profile with time mode
- L121 _public member_ `TSharedPtr< FUICommandInfo > CreateWeightBlendProfile;` — Create a new blend profile with weight mode
- L124 _public member_ `TSharedPtr< FUICommandInfo > CreateBlendMask;` — Create a new blend mask
- L127 _public member_ `TSharedPtr< FUICommandInfo > DeleteCurrentBlendProfile;` — Remove the currently active blend profile
- L130 _public member_ `TSharedPtr< FUICommandInfo > RenameBlendProfile;` — Rename an existing BlendProfile

### `Source/Editor/SkeletonEditor/Private/SkeletonTreeManager.h` (Private)


#### class `FSkeletonTreeManager`  
`class FSkeletonTreeManager`  
_L14-36_
- desc: Central registry of skeleton trees
- L18 _public prototype_ `static FSkeletonTreeManager& Get();` — Singleton access
- L21 _public prototype_ `TSharedRef<ISkeletonTree> CreateSkeletonTree(const TSharedRef<IEditableSkeleton>& InEditableSkeleton, const FSkeletonTreeArgs& InSkeletonTreeArgs);` — Create a skeleton tree for the given an already-existing editable skeleton
- L24 _public prototype_ `TSharedRef<ISkeletonTree> CreateSkeletonTree(USkeleton* InSkeleton, const FSkeletonTreeArgs& InSkeletonTreeArgs);` — Create a skeleton tree for the requested skeleton
- L27 _public prototype_ `TSharedRef<FEditableSkeleton> CreateEditableSkeleton(USkeleton* InSkeleton);` — Edit a USkeleton via FEditableSkeleton
- L31 _private function_ `FSkeletonTreeManager()` — Hidden constructor
- L35 _private member_ `TMap<USkeleton*, TWeakPtr<FEditableSkeleton>> EditableSkeletons;` — Map from skeletons to editable skeletons

### `Source/Editor/SkeletonEditor/Private/SkeletonTreeMenuContext.h` (Private)


#### class `USkeletonTreeMenuContext`  
`class USkeletonTreeMenuContext : public UObject`  
_L9-16_
- reflection: `UCLASS()`
- inherits: `UObject`
- L15 _public member_ `TWeakPtr<SSkeletonTree> SkeletonTree;` — The skeleton tree we reference

### `Source/Editor/SkeletonEditor/Private/SkeletonTreeSocketItem.h` (Private)


#### class `FSkeletonTreeSocketItem`  
`class FSkeletonTreeSocketItem : public FSkeletonTreeItem`  
_L18-87_
- inherits: `FSkeletonTreeItem`
- L21 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreeSocketItem, FSkeletonTreeItem) FSkeletonTreeSocketItem(USkeletalMeshSocket* InSocket, ESocketParentType InParentType, bool bInIsCustomized, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L28 _public prototype_ `virtual void GenerateWidgetForNameColumn(TSharedPtr< SHorizontalBox > Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;` — ISkeletonTreeItem interface
- L29 _public prototype_ `virtual TSharedRef< SWidget > GenerateWidgetForDataColumn(const FName& DataColumnName, FIsSelected InIsSelected) override;`
- L30 _public prototype_ `virtual TSharedRef< SWidget > GenerateInlineEditWidget(const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;`
- L31 _public function_ `virtual bool HasInlineEditor() const override`
- L32 _public function_ `virtual void ToggleInlineEditorExpansion() override`
- L33 _public function_ `virtual bool IsInlineEditorExpanded() const override`
- L34 _public function_ `virtual FName GetRowItemName() const override`
- L35 _public function_ `virtual bool CanRenameItem() const override`
- L36 _public prototype_ `virtual void RequestRename() override;`
- L37 _public prototype_ `virtual void OnItemDoubleClicked() override;`
- L38 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L39 _public function_ `virtual UObject* GetObject() const override`
- L42 _public function_ `ESocketParentType GetParentType() const` — Get the parent type
- L45 _public function_ `bool IsSocketCustomized() const` — Is this socket customized
- L48 _public prototype_ `bool CanCustomizeSocket() const;` — Can we customize this socket?
- L51 _public function_ `USkeletalMeshSocket* GetSocket() const` — Get the socket we wrap
- L55 _private prototype_ `bool OnVerifySocketNameChanged(const FText& InText, FText& OutErrorMessage);` — Called when user is renaming a socket to verify the name
- L58 _private prototype_ `void OnCommitSocketName(const FText& InText, ETextCommit::Type CommitInfo);` — Called when user renames a socket
- L61 _private prototype_ `FText GetSocketToolTip() const;` — Function that returns the current tooltip for this socket
- L64 _private prototype_ `FSlateColor GetTextColor() const;` — Get the color to display for the socket name
- L67 _private function_ `FText GetSocketNameAsText() const` — Return socket name as FText for display in skeleton tree
- L71 _private member_ `USkeletalMeshSocket* Socket;` — The socket we represent
- L74 _private member_ `ESocketParentType ParentType;` — Whether we are on the skeleton or the mesh
- L77 _private member_ `bool bIsCustomized;` — Whether we are customized
- L80 _private member_ `bool bInlineEditorExpanded;` — Track expansion state of the in-line editor
- L83 _private prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L84 _private member_ `FOnRenameRequested OnRenameRequested;`
- L86 _private member_ `FDelegateHandle OnSocketChangedDelegate;`

#### Free symbols / members of external scopes

- L83 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename

### `Source/Editor/SkeletonEditor/Private/SkeletonTreeSummoner.h` (Private)


#### struct `FSkeletonTreeSummoner`  
`struct FSkeletonTreeSummoner : public FWorkflowTabFactory`  
_L13-24_
- inherits: `FWorkflowTabFactory`
- L16 _public prototype_ `FSkeletonTreeSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, TSharedRef<class ISkeletonTree> InSkeletonTree);`
- L19 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L20 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L23 _public member_ `TWeakPtr<class ISkeletonTree> SkeletonTreePtr;` — Reference to our skeleton tree

### `Source/Editor/SkeletonEditor/Private/SkeletonTreeVirtualBoneItem.h` (Private)


#### class `FSkeletonTreeVirtualBoneItem`  
`class FSkeletonTreeVirtualBoneItem : public FSkeletonTreeItem, public FGCObject`  
_L20-124_
- inherits: `FSkeletonTreeItem,FGCObject`
- L23 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreeVirtualBoneItem, FSkeletonTreeItem) FSkeletonTreeVirtualBoneItem(const FName& InBoneName, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L28 _public prototype_ `virtual void GenerateWidgetForNameColumn(TSharedPtr< SHorizontalBox > Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;` — Builds the table row widget to display this info
- L29 _public prototype_ `virtual TSharedRef< SWidget > GenerateWidgetForDataColumn(const FName& DataColumnName, FIsSelected InIsSelected) override;`
- L30 _public function_ `virtual FName GetRowItemName() const override`
- L31 _public function_ `virtual bool CanRenameItem() const override`
- L32 _public prototype_ `virtual void RequestRename() override;`
- L33 _public prototype_ `virtual void OnItemDoubleClicked() override;`
- L34 _public prototype_ `virtual void HandleDragEnter(const FDragDropEvent& DragDropEvent) override;`
- L35 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L36 _public prototype_ `virtual FReply HandleDrop(const FDragDropEvent& DragDropEvent) override;`
- L37 _public function_ `virtual UObject* GetObject() const override`
- L40 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L41 _public function_ `virtual FString GetReferencerName() const override`
- L47 _public function_ `FText GetVirtualBoneNameAsText() const` — Return socket name as FText for display in skeleton tree
- L50 _public prototype_ `void EnableBoneProxyTick(bool bEnable);` — Enable and disable the bone proxy ticking
- L55 _private prototype_ `void OnBlendSliderCommitted(float NewValue, ETextCommit::Type CommitType);` — Callback from a slider widget if the text entry is used
- L58 _private prototype_ `void OnBlendSliderChanged(float NewValue);` — Callback from a slider widget if the slider is used
- L61 _private prototype_ `void OnBeginBlendSliderMovement();` — Callback from a slider widget when the user begins sliding
- L64 _private prototype_ `void OnEndBlendSliderMovement(float NewValue);` — Callback from a slider widget when the user has finished sliding
- L67 _private prototype_ `void SetBoneTranslationRetargetingMode(EBoneTranslationRetargetingMode::Type NewRetargetingMode);` — Set Translation Retargeting Mode for this bone.
- L70 _private prototype_ `float GetBoneBlendProfileScale() const;` — Get the current Blend Scale for this bone
- L73 _private prototype_ `TOptional<float> GetBlendProfileMaxSliderValue() const;` — Get the max slider value supported by the selected blend profile's mode
- L76 _private prototype_ `TOptional<float> GetBlendProfileMinSliderValue() const;` — Get the min slider value supported by the selected blend profile's mode
- L79 _private prototype_ `EVisibility GetBoneBlendProfileVisibility() const;` — Used to hide the Bone Profile row widget if there is no current Blend Profile
- L82 _private prototype_ `void OnVirtualBoneNameEditing();` — Called when we are about to rename a virtual bone
- L85 _private prototype_ `bool OnVerifyBoneNameChanged(const FText& InText, FText& OutErrorMessage);` — Called when user is renaming this bone to verify the name
- L88 _private prototype_ `void OnCommitVirtualBoneName(const FText& InText, ETextCommit::Type CommitInfo);` — Called when user renames this bone
- L91 _private prototype_ `EVisibility GetVirtualBonePrefixVisibility() const;` — Called to get the visibility of the Prefix label during rename
- L94 _private prototype_ `FSlateFontInfo GetBoneTextFont() const;` — Gets the font for displaying bone text in the skeletal tree
- L97 _private prototype_ `FSlateColor GetBoneTextColor(FIsSelected InIsSelected) const;` — Get the text color based on bone part of skeleton or part of mesh
- L100 _private prototype_ `EVisibility GetLODIconVisibility() const;` — visibility of the icon
- L103 _private prototype_ `FText GetBoneToolTip();` — Function that returns the current tooltip for this bone, depending on how it's used by the mesh
- L106 _private member_ `FName BoneName;` — The actual bone data that we create Slate widgets to display
- L109 _private member_ `FName CachedBoneNameForRename;` — During rename we modify the name slightly (strip off the VB prefix) cache the original name here
- L113 _private member_ `TSharedPtr< SInlineEditableTextBlock > InlineWidget;` — TSharedPtr<SEditableText> NameEntryBox;
- L116 _private prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L117 _private member_ `FOnRenameRequested OnRenameRequested;`
- L120 _private member_ `TObjectPtr<UBoneProxy> BoneProxy;` — Bone proxy used for debug display
- L123 _private member_ `bool bBlendSliderStartedTransaction;` — True if the user is in a transaction when moving the blend profile slider

#### Free symbols / members of external scopes

- L116 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename

### `Source/Editor/SkeletonEditor/Public/BlendProfilePicker.h` (Public)


#### enum `EBlendProfilePickerMode`  
`enum class EBlendProfilePickerMode : uint8`  
_L11-16_
- L13 _public enumerator_ `BlendProfile = (1U << 0)`
- L14 _public enumerator_ `BlendMask = (1U << 1)`
- L15 _public enumerator_ `AllModes = BlendProfile | BlendMask`

#### struct `FBlendProfilePickerArgs`  
`struct FBlendProfilePickerArgs`  
_L20-52_
- desc: Argument used to set up the blend profile picker
- L23 _public member_ `UBlendProfile* InitialProfile;` — Initial blend profile selected
- L26 _public member_ `FOnBlendProfileSelected OnBlendProfileSelected;` — Delegate to call when the picker selection is changed
- L29 _public member_ `bool bAllowNew;` — Allow the option to create new profiles in the picker
- L32 _public member_ `bool bAllowClear;` — Allow the option to clear the profile selection
- L35 _public member_ `bool bAllowModify;` — Allow the option to delete blend profiles from the skeleton
- L38 _public member_ `EBlendProfilePickerMode SupportedBlendProfileModes;` — Only display Blend Profiles w/ specified Blend Profile modes (EBlendProfilePickerMode values are flags.)
- L41 _public member_ `TSharedPtr<class IPropertyHandle> PropertyHandle;` — Optional property handle, when the picker is tied to a property
- L43 _public function_ `FBlendProfilePickerArgs() : InitialProfile(nullptr) , OnBlendProfileSelected() , bAllowNew(false) , bAllowClear(false) , bAllowModify(false) , SupportedBlendProfileModes(EBlendProfilePickerMode::AllModes) , PropertyHandle(nullptr)`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBlendProfileSelected, UBlendProfile*);`
- L9 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBlendProfileSelected, UBlendProfile*);`
- L17 _prototype_ `ENUM_CLASS_FLAGS(EBlendProfilePickerMode);`

### `Source/Editor/SkeletonEditor/Public/BoneProxy.h` (Public)


#### class `UBoneProxy`  
`class UBoneProxy : public UObject, public FTickableEditorObject`  
_L24-178_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,FTickableEditorObject`
- desc: Proxy object used to display/edit bone transforms
- L29 _public prototype_ `UBoneProxy();`
- L46 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& PropertyAboutToChange) override;` — UObject interface
- L47 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _public prototype_ `void OnPreEditChange(FName PropertyName);` — overload based on a property name
- L51 _public prototype_ `void OnPostEditChangeProperty(FName PropertyName);`
- L54 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject interface
- L55 _public prototype_ `virtual bool IsTickable() const override;`
- L56 _public prototype_ `virtual TStatId GetStatId() const override;`
- L60 _public member_ `FName BoneName;` — `UPROPERTY(VisibleAnywhere, Category = "Bone")` — The name of the bone we have selected
- L64 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, Category = "Transform")` — Bone location
- L68 _public member_ `FRotator Rotation;` — `UPROPERTY(EditAnywhere, Category = "Transform")` — Bone rotation
- L72 _public member_ `FVector Scale;` — `UPROPERTY(EditAnywhere, Category = "Transform")` — Bone scale
- L76 _public member_ `FVector ReferenceLocation;` — `UPROPERTY(VisibleAnywhere, Category = "Reference Transform")` — Bone reference location (local)
- L80 _public member_ `FRotator ReferenceRotation;` — `UPROPERTY(VisibleAnywhere, Category = "Reference Transform")` — Bone reference rotation (local)
- L84 _public member_ `FVector ReferenceScale;` — `UPROPERTY(VisibleAnywhere, Category = "Reference Transform")` — Bone reference scale (local)
- L88 _public member_ `FVector MeshLocation;` — `UPROPERTY(VisibleAnywhere, Category = "Mesh Relative Transform")` — Mesh Location. Non zero when processing root motion
- L92 _public member_ `FRotator MeshRotation;` — `UPROPERTY(VisibleAnywhere, Category = "Mesh Relative Transform")` — Mesh Rotation. Non zero when processing root motion
- L96 _public member_ `FVector MeshScale;` — `UPROPERTY(VisibleAnywhere, Category = "Mesh Relative Transform")` — Mesh Scale
- L100 _public member_ `TWeakObjectPtr<UDebugSkelMeshComponent> SkelMeshComponent;` — `UPROPERTY()` — The skeletal mesh component we glean our transform data from
- L102 _public member_ `TWeakPtr<IPersonaPreviewScene> WeakPreviewScene;`
- L105 _public member_ `bool bLocalLocation;` — Whether to use local or world location
- L108 _public member_ `bool bLocalRotation;` — Whether to use local or world rotation
- L111 _public member_ `bool bLocalScale;` — Whether to use local or world rotation
- L114 _public member_ `FVector PreviousLocation;` — Handle property deltas
- L115 _public member_ `FRotator PreviousRotation;`
- L116 _public member_ `FVector PreviousScale;`
- L119 _public member_ `bool bManipulating;` — Flag indicating we are in the middle of a drag operation
- L122 _public member_ `bool bIsTickable;` — Flag indicating whether this FTickableEditorObject should actually tick
- L125 _public member_ `bool bIsTransformEditable;` — Flag indicating whether this bone's transform is editable
- L128 _public prototype_ `TOptional<FVector::FReal> GetNumericValue( ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, ETransformType TransformType) const;` — Method to react to retrieval of numeric values for the widget
- L135 _public prototype_ `static TOptional<FVector::FReal> GetMultiNumericValue( ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, ETransformType TransformType, TArrayView<UBoneProxy*> BoneProxies);` — Static method to retrieve a value for a list of proxies
- L143 _public prototype_ `void OnNumericValueChanged( ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, FVector::FReal Value, ETransformType TransformType);` — Method to react to changes of numeric values in the widget
- L150 _public prototype_ `static void OnSliderMovementStateChanged( ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, FVector::FReal Value, ESliderMovementState SliderMovementState, TArrayView<UBoneProxy*> BoneProxies);`
- L159 _public prototype_ `static void OnMultiNumericValueChanged( ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, FVector::FReal Value, ETextCommit::Type InCommitType, bool bInTransactional, ETransformType TransformType, TArrayView<UBoneProxy*> BoneProxies);` — Method to react to changes of numeric values in the widget
- L170 _public prototype_ `bool DiffersFromDefault(ESlateTransformComponent::Type Component, ETransformType TransformType) const;` — Returns true if a given transform component differs from the reference
- L173 _public prototype_ `void ResetToDefault(ESlateTransformComponent::Type InComponent, ETransformType TransformType);` — Resets the bone transform's component to its reference
- L176 _private prototype_ `static void BeginSetValueTransaction(ESlateTransformComponent::Type InComponent, TArrayView<UBoneProxy*> BoneProxies);`
- L177 _private prototype_ `static void EndTransaction();`

#### enum `UBoneProxy::ETransformType`  
`enum ETransformType`  
_L31-36_
- L33 _public enumerator_ `TransformType_Bone`
- L34 _public enumerator_ `TransformType_Reference`
- L35 _public enumerator_ `TransformType_Mesh`

#### enum `UBoneProxy::ESliderMovementState`  
`enum class ESliderMovementState`  
_L38-42_
- L40 _public enumerator_ `Begin`
- L41 _public enumerator_ `End`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SKELETONEDITOR_API`
- L17 _namespace_ `namespace ESlateTransformComponent`
- L18 _namespace_ `namespace ESlateRotationRepresentation`
- L19 _namespace_ `namespace ESlateTransformSubComponent`
- L20 _namespace_ `namespace ETextCommit`

### `Source/Editor/SkeletonEditor/Public/IEditableSkeleton.h` (Public)


#### enum `ESocketParentType`  
`enum class ESocketParentType : int32`  
_L17-21_
- desc: Enum which tells us whether the parent of a socket is the skeleton or skeletal mesh
- L19 _public enumerator_ `Skeleton`
- L20 _public enumerator_ `Mesh`

#### class `IEditableSkeleton`  
`class IEditableSkeleton`  
_L24-207_
- desc: Interface used to deal with skeletons that are currently being edited
- L28 _public prototype_ `virtual const class USkeleton& GetSkeleton() const = 0;` — Get the skeleton. Const - to modify the skeleton you should use the wrapper methods below. Use IsSkeletonValid first, as the Skeleton is not guaranteed to exist.
- L31 _public prototype_ `virtual bool IsSkeletonValid() const = 0;` — Checks to see if the editable skeleton is valid. It is possible for Skeleton to be non-existent (if deleted externally).
- L34 _public prototype_ `virtual const TArray<class UBlendProfile*>& GetBlendProfiles() const = 0;` — Get the blend profiles that this skeleton currently contains
- L37 _public prototype_ `virtual class UBlendProfile* GetBlendProfile(const FName& InBlendProfileName) = 0;` — Get the named blend profile @return nullptr if none was found
- L40 _public prototype_ `virtual class UBlendProfile* CreateNewBlendProfile(const FName& InBlendProfileName) = 0;` — Create the named blend profile
- L43 _public prototype_ `virtual void RemoveBlendProfile(UBlendProfile* InBlendProfile) = 0;` — Remove the specifed blend profile
- L46 _public prototype_ `virtual class UBlendProfile* RenameBlendProfile(const FName& InBlendProfileName, const FName& InNewBlendProfileName) = 0;` — Rename an existing blend profile
- L49 _public prototype_ `virtual void SetBlendProfileScale(const FName& InBlendProfileName, const FName& InBoneName, float InNewScale, bool bInRecurse) = 0;` — Set the blend profile scale for the specified bone
- L52 _public prototype_ `virtual void SetBlendProfileMode(FName InBlendProfileName, EBlendProfileMode ProfileMode) = 0;` — Change an existing blend profile's mode (See EBlendProfileMode for details)
- L55 _public prototype_ `virtual USkeletalMeshSocket* AddSocket(const FName& InBoneName) = 0;` — Creates a new socket on the skeleton
- L58 _public prototype_ `virtual class USkeletalMeshSocket* DuplicateSocket(const struct FSelectedSocketInfo& SocketInfoToDuplicate, const FName& NewParentBoneName, USkeletalMesh* InSkeletalMesh) = 0;` — Handle drag-drop socket duplication
- L61 _public prototype_ `virtual void RenameSocket(const FName OldSocketName, const FName NewSocketName, USkeletalMesh* InSkeletalMesh) = 0;` — Rename a socket on the mesh or the skeleton
- L64 _public prototype_ `virtual void SetSocketParent(const FName& SocketName, const FName& NewParentName, USkeletalMesh* InSkeletalMesh, bool bKeepAbsoluteLocation = false) = 0;` — Set the parent of a socket
- L67 _public prototype_ `virtual bool DoesSocketAlreadyExist(const class USkeletalMeshSocket* InSocket, const FText& InSocketName, ESocketParentType SocketParentType, USkeletalMesh* InSkeletalMesh) const = 0;` — Function to tell you if a socket name already exists. SocketParentType determines where we will look to see if the socket exists, i.e. mesh or skeleton
- L74 _public prototype_ `virtual int32 ValidatePreviewAttachedObjects() = 0;` — Makes sure all attached objects are valid and removes any that aren't. @return		NumberOfBrokenAssets
- L85 _public prototype_ `virtual void RecreateBoneTree(class USkeletalMesh* NewPreviewMesh) = 0;` — Merge has failed, then Recreate BoneTree This will invalidate all animations that were linked before, but this is needed @param InSkelMesh			: Mesh to build from. @return true if success
- L91 _public prototype_ `virtual int32 DeleteAnimNotifies(const TArray<FName>& InotifyNames, bool bDeleteFromAnimations = true) = 0;` — Delete anim notifies by name @return the number of animations modified
- L97 _public prototype_ `virtual int32 DeleteSyncMarkers(const TArray<FName>& ISyncMarkerNames, bool bDeleteFromAnimations = true) = 0;` — Delete sync markers from the skeleton cache by name @return the number of animations modified
- L102 _public prototype_ `virtual void AddNotify(FName NewName) = 0;` — Add a notify
- L108 _public prototype_ `virtual int32 RenameNotify(const FName NewName, const FName OldName, bool bRenameInAnimations = true) = 0;` — Rename a notify @return the number of animations modified
- L113 _public prototype_ `virtual void AddSyncMarker(FName NewName) = 0;` — Add a sync marker
- L119 _public prototype_ `virtual int32 RenameSyncMarker(FName NewName, const FName OldName, bool bRenameInAnimations = true) = 0;` — Rename a sync marker @return the number of animations modified
- L122 _public prototype_ `virtual void BroadcastNotifyChanged() = 0;` — Inform the system that something about a notify changed
- L125 _public prototype_ `virtual void GetCompatibleAnimSequences(TArray<struct FAssetData>& OutAssets) = 0;` — Populates OutAssets with the AnimSequences that match this current skeleton
- L128 _public prototype_ `virtual void SetPreviewMesh(class USkeletalMesh* InSkeletalMesh) = 0;` — Set the preview mesh in the skeleton
- L131 _public prototype_ `virtual void LoadAdditionalPreviewSkeletalMeshes() = 0;` — Load any additional meshes we may have
- L134 _public prototype_ `virtual void SetAdditionalPreviewSkeletalMeshes(class UDataAsset* InPreviewCollectionAsset) = 0;` — Set the additional skeletal meshes we use when previewing this skeleton
- L137 _public prototype_ `virtual void RenameRetargetSource(const FName InOldName, const FName InNewName) = 0;` — Rename the specified retarget source
- L140 _public prototype_ `virtual void AddRetargetSource(const FName& InName, USkeletalMesh* InReferenceMesh) = 0;` — Add a retarget source
- L143 _public prototype_ `virtual void DeleteRetargetSources(const TArray<FName>& InRetargetSourceNames) = 0;` — Delete retarget sources
- L146 _public prototype_ `virtual void RefreshRetargetSources(const TArray<FName>& InRetargetSourceNames) = 0;` — Refresh retarget sources
- L149 _public prototype_ `virtual void AddCompatibleSkeleton(const USkeleton* InCompatibleSkeleton) = 0;` — Add a compatible skeleton
- L152 _public prototype_ `virtual void RemoveCompatibleSkeleton(const USkeleton* InCompatibleSkeleton) = 0;` — Remove a compatible skeleton
- L155 _public prototype_ `virtual void RemoveUnusedBones() = 0;` — Remove any bones that are not used by any skeletal meshes
- L158 _public prototype_ `virtual void FindUnusedBones(TArray<FName>& OutUnusedBones, bool bSilent = false) = 0;` — Returns a list of all bones that are not used by any skeletal meshes
- L161 _public prototype_ `virtual void UpdateSkeletonReferencePose(class USkeletalMesh* InSkeletalMesh) = 0;` — Create RefLocalPoses from InSkeletalMesh
- L164 _public prototype_ `virtual void RegisterSlotNode(const FName& InSlotName) = 0;` — Register a slot node
- L167 _public prototype_ `virtual bool AddSlotGroupName(const FName& InSlotName) = 0;` — Add a slot group name
- L170 _public prototype_ `virtual void SetSlotGroupName(const FName& InSlotName, const FName& InGroupName) = 0;` — Set the group name of the specified slot
- L173 _public prototype_ `virtual void DeleteSlotName(const FName& InSlotName) = 0;` — Delete a slot name
- L176 _public prototype_ `virtual void DeleteSlotGroup(const FName& InGroupName) = 0;` — Delete a slot group
- L179 _public prototype_ `virtual void RenameSlotName(const FName InOldSlotName, const FName InNewSlotName) = 0;` — Rename a slot name
- L182 _public prototype_ `virtual void RegisterOnNotifiesChanged(const FSimpleMulticastDelegate::FDelegate& InDelegate) = 0;` — Register a delegate to be called when this skeletons notifies are changed
- L185 _public prototype_ `virtual void UnregisterOnNotifiesChanged(FDelegateUserObject Thing) = 0;` — Unregister a delegate to be called when this skeletons notifies are changed
- L188 _public prototype_ `virtual FDelegateHandle RegisterOnSlotsChanged(const FSimpleMulticastDelegate::FDelegate& InDelegate) = 0;` — Register a delegate to be called when this skeletons slots are changed
- L191 _public prototype_ `virtual void UnregisterOnSlotsChanged(FDelegateHandle InHandle) = 0;` — Unregister a delegate to be called when this skeletons slots are changed
- L194 _public prototype_ `virtual void SetBoneTranslationRetargetingMode(FName InBoneName, EBoneTranslationRetargetingMode::Type NewRetargetingMode) = 0;` — Wrap USkeleton::SetBoneTranslationRetargetingMode
- L197 _public prototype_ `virtual EBoneTranslationRetargetingMode::Type GetBoneTranslationRetargetingMode(FName InBoneName) const = 0;` — Wrap USkeleton::GetBoneTranslationRetargetingMode
- L200 _public prototype_ `virtual bool DoesVirtualBoneAlreadyExist(const FString& InVBName) const = 0;` — Function to tell you if a virtual bone name is already in use
- L203 _public prototype_ `virtual void RenameVirtualBone(const FName OriginalName, const FName InVBName) = 0;` — Rename an existing virtual bone
- L206 _public prototype_ `virtual void RefreshBoneTree() = 0;` — Broadcasts tree refresh delegate

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSmartNameChanged, const FName& );` — Delegate fired when a set of smart names is removed
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSmartNameChanged, const FName& );` — Delegate fired when a set of smart names is removed

### `Source/Editor/SkeletonEditor/Public/ISkeletonEditor.h` (Public)


#### class `ISkeletonEditor`  
`class ISkeletonEditor : public FPersonaAssetEditorToolkit, public IHasPersonaToolkit`  
_L11-16_
- inherits: `FPersonaAssetEditorToolkit,IHasPersonaToolkit`
- L15 _public prototype_ `virtual IAnimationSequenceBrowser* GetAssetBrowser() const = 0;` — Get the asset browser we host

### `Source/Editor/SkeletonEditor/Public/ISkeletonEditorModule.h` (Public)


#### class `ISkeletonEditorModule`  
`class ISkeletonEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L20-44_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- L24 _public prototype_ `virtual TSharedRef<ISkeletonEditor> CreateSkeletonEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, class USkeleton* InSkeleton) = 0;` — Creates a new skeleton editor instance
- L27 _public prototype_ `virtual TSharedRef<ISkeletonTree> CreateSkeletonTree(USkeleton* InSkeleton, const FSkeletonTreeArgs& InSkeletonTreeArgs) = 0;` — Creates a new skeleton tree instance
- L30 _public prototype_ `virtual TSharedRef<ISkeletonTree> CreateSkeletonTree(const TSharedRef<IEditableSkeleton>& InEditableSkeleton, const FSkeletonTreeArgs& InSkeletonTreeArgs) = 0;` — Creates a new skeleton tree instance
- L33 _public prototype_ `virtual TSharedRef<class FWorkflowTabFactory> CreateSkeletonTreeTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<ISkeletonTree>& InSkeletonTree) = 0;` — Creates a new skeleton tree instance & registers a tab factory with the supplied tab factories
- L36 _public prototype_ `virtual TSharedRef<IEditableSkeleton> CreateEditableSkeleton(USkeleton* InSkeleton) = 0;` — Creates a new editable skeleton instance
- L39 _public prototype_ `virtual TSharedRef<SWidget> CreateBlendProfilePicker(USkeleton* InSkeleton, const FBlendProfilePickerArgs& InArgs = FBlendProfilePickerArgs()) = 0;` — Creates a new blend profile picker instance
- L42 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FSkeletonEditorToolbarExtender, const TSharedRef<FUICommandList> , TSharedRef<ISkeletonEditor> );` — Get all toolbar extenders
- L43 _public prototype_ `virtual TArray<FSkeletonEditorToolbarExtender>& GetAllSkeletonEditorToolbarExtenders() = 0;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletonEditor, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletonEditor, Log, All);`
- L42 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FSkeletonEditorToolbarExtender, const TSharedRef<FUICommandList> , TSharedRef<ISkeletonEditor> );` — Get all toolbar extenders

### `Source/Editor/SkeletonEditor/Public/ISkeletonTree.h` (Public)


#### enum `ESkeletonTreeMode`  
`enum class ESkeletonTreeMode`  
_L34-41_
- L37 _public enumerator_ `Editor` — Skeleton tree allows editing
- L40 _public enumerator_ `Picker` — Skeleton tree allows picking of tree elements

#### struct `FSkeletonTreeArgs`  
`struct FSkeletonTreeArgs`  
_L44-99_
- desc: Init params for a skeleton tree widget
- L46 _public function_ `FSkeletonTreeArgs() : Mode(ESkeletonTreeMode::Editor) , ContextName(TEXT("SkeletonTree")) , bShowBlendProfiles(true) , bShowFilterMenu(true) , bShowDebugVisualizationOptions(false) , bAllowMeshOperations(true) , bAllowSkeletonOperations(true) , bHideBonesByDefault(false) , bAllowInvisibleItemSelection(false)`
- L59 _public member_ `FOnSkeletonTreeSelectionChanged OnSelectionChanged;` — Delegate called by the tree when a socket is selected
- L62 _public member_ `FOnGetFilterText OnGetFilterText;` — Delegate that allows custom filtering text to be shown on the filter button
- L65 _public member_ `TSharedPtr<IPersonaPreviewScene> PreviewScene;` — Optional preview scene that we can pair with
- L68 _public member_ `TSharedPtr<ISkeletonTreeBuilder> Builder;` — Optional builder to allow for custom tree construction
- L71 _public member_ `TSharedPtr<FExtender> Extenders;` — Menu extenders applied to context and filter menus
- L74 _public member_ `ESkeletonTreeMode Mode;` — The mode that this skeleton tree is in
- L77 _public member_ `FName ContextName;` — Context name used to persist settings
- L80 _public member_ `bool bShowBlendProfiles;` — Whether to show the blend profiles editor for the skeleton being displayed
- L83 _public member_ `bool bShowFilterMenu;` — Whether to show the filter menu to allow filtering of active bones, sockets etc.
- L86 _public member_ `bool bShowDebugVisualizationOptions;` — Whether to show the filter option to allow filtering of debug draw elements in the viewport.
- L89 _public member_ `bool bAllowMeshOperations;` — Whether to allow operations that modify the mesh
- L92 _public member_ `bool bAllowSkeletonOperations;` — Whether to allow operations that modify the skeleton
- L95 _public member_ `bool bHideBonesByDefault;` — Whether to hide bones by default
- L98 _public member_ `bool bAllowInvisibleItemSelection;` — Wether children can remain selected while their parent is collapsed in the tree

#### class `ISkeletonTree`  
`class ISkeletonTree : public SCompoundWidget`  
_L102-175_
- inherits: `SCompoundWidget`
- desc: Interface used to deal with skeleton editing UI
- L113 _public function_ `static const FName DebugVisualizationOptionsName()`
- L116 _public prototype_ `virtual void Refresh() = 0;` — Manually refresh the tree
- L119 _public prototype_ `virtual void RefreshFilter() = 0;` — Manually refresh the tree filter
- L122 _public prototype_ `virtual TSharedRef<class IEditableSkeleton> GetEditableSkeleton() const = 0;` — Get editable skeleton that this widget is editing
- L125 _public prototype_ `virtual TSharedPtr<class IPersonaPreviewScene> GetPreviewScene() const = 0;` — Get preview scene that this widget is editing
- L128 _public prototype_ `virtual void SetSkeletalMesh(class USkeletalMesh* NewSkeletalMesh) = 0;` — Set the skeletal mesh we optionally work with
- L131 _public prototype_ `virtual void SetSelectedSocket(const struct FSelectedSocketInfo& InSocketInfo) = 0;` — Set the selected socket
- L135 _public function_ `virtual void SetSelectedBone(const FName& InBoneName) final` — `UE_DEPRECATED(4.26, "Please call/implement SetSelectedBone with ESelectInfo")` — Set the selected bone
- L138 _public prototype_ `virtual void SetSelectedBone(const FName& InBoneName, ESelectInfo::Type InSelectInfo) = 0;` — Set the selected bone
- L141 _public prototype_ `virtual void SetSelectedBones(const TArray<FName>& InBoneNames, ESelectInfo::Type InSelectInfo) = 0;` — Set the selected bone(s)
- L144 _public prototype_ `virtual void DeselectAll() = 0;` — Deselect everything that is currently selected
- L147 _public prototype_ `virtual TArray<TSharedPtr<ISkeletonTreeItem>> GetSelectedItems() const = 0;` — Get the selected items
- L150 _public prototype_ `virtual void SelectItemsBy(TFunctionRef<bool(const TSharedRef<ISkeletonTreeItem>& , bool& )> Predicate, const ESelectInfo::Type SelectInfo = ESelectInfo::Direct) const = 0;` — Select items using the passed in predicate
- L153 _public prototype_ `virtual void DuplicateAndSelectSocket(const FSelectedSocketInfo& SocketInfoToDuplicate, const FName& NewParentBoneName = FName()) = 0;` — Duplicate the socket and select it
- L156 _public prototype_ `virtual FDelegateHandle RegisterOnSelectionChanged(const FOnSkeletonTreeSelectionChanged& Delegate) = 0;` — Registers a delegate to be called when the selected items have changed
- L159 _public prototype_ `virtual void UnregisterOnSelectionChanged(FDelegateHandle DelegateHandle) = 0;` — Unregisters a delegate to be called when the selected items have changed
- L162 _public prototype_ `virtual UBlendProfile* GetSelectedBlendProfile() = 0;` — Gets the currently selected blend profile
- L165 _public prototype_ `virtual void AttachAssets(const TSharedRef<class ISkeletonTreeItem>& TargetItem, const TArray<FAssetData>& AssetData) = 0;` — Attached the supplied assets to the tree to the specified attach item (bone/socket)
- L168 _public prototype_ `virtual TSharedPtr<SWidget> GetSearchWidget() const = 0;` — Get the search box widget, if any, for this tree
- L171 _public prototype_ `virtual TSharedPtr<IPinnedCommandList> GetPinnedCommandList() const = 0;` — Get the pinned commands widget, if any, for this tree
- L174 _public prototype_ `virtual void ResetBoneTransforms(const bool bSelectedOnly) = 0;` — Function to reset the transforms of selected bones

#### struct `ISkeletonTree::Columns`  
`struct Columns`  
_L105-111_
- L107 _public member_ `static const FName Name;`
- L108 _public member_ `static const FName Retargeting;`
- L109 _public member_ `static const FName BlendProfile;`
- L110 _public member_ `static const FName DebugVisualization;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSkeletonTreeSelectionChangedMulticast, const TArrayView<TSharedPtr<ISkeletonTreeItem>>& , ESelectInfo::Type );` — Called when an item is selected/deselected
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSkeletonTreeSelectionChangedMulticast, const TArrayView<TSharedPtr<ISkeletonTreeItem>>& , ESelectInfo::Type );` — Called when an item is selected/deselected
- L23 _typedef_ `typedef FOnSkeletonTreeSelectionChangedMulticast::FDelegate FOnSkeletonTreeSelectionChanged;` — Called when an item is selected/deselected
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectSelectedMulticast, UObject* );` — Called when a bone is selected - DEPRECATED, please use FOnSkeletonTreeSelectionChangedMulticast
- L26 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectSelectedMulticast, UObject* );` — Called when a bone is selected - DEPRECATED, please use FOnSkeletonTreeSelectionChangedMulticast
- L29 _typedef_ `typedef FOnObjectSelectedMulticast::FDelegate FOnObjectSelected;` — Called when an object is selected - DEPRECATED, please use FOnSkeletonTreeSelectionChanged
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetFilterText, TArray<FText>& );` — Delegate that allows custom filtering text to be shown on the filter button
- L32 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGetFilterText, TArray<FText>& );` — Delegate that allows custom filtering text to be shown on the filter button

### `Source/Editor/SkeletonEditor/Public/ISkeletonTreeBuilder.h` (Public)


#### struct `FSkeletonTreeBuilderOutput`  
`struct FSkeletonTreeBuilderOutput`  
_L16-86_
- desc: Output struct for builders to use
- L18 _public function_ `FSkeletonTreeBuilderOutput(TArray<TSharedPtr<class ISkeletonTreeItem>>& InItems, TArray<TSharedPtr<class ISkeletonTreeItem>>& InLinearItems) : Items(InItems) , LinearItems(InLinearItems)`
- L30 _public prototype_ `void Add(const TSharedPtr<class ISkeletonTreeItem>& InItem, const FName& InParentName, TArrayView<const FName> InParentTypes, bool bAddToHead = false);` — Add an item to the output @param	InItem			The item to add @param	InParentName	The name of the item's parent @param	InParentTypes	The types of items to search. If this is empty all items will be searched. @param	bAddToHead		Whether to add the item to the start or end of the parent's children array
- L39 _public function_ `FORCEINLINE void Add(const TSharedPtr<class ISkeletonTreeItem>& InItem, const FName& InParentName, std::initializer_list<FName> InParentTypes, bool bAddToHead = false)` — Add an item to the output @param	InItem			The item to add @param	InParentName	The name of the item's parent @param	InParentTypes	The types of items to search. If this is empty all items will be searched. @param	bAddToHead		Whether to add the item to the start or end of the parent's children array
- L51 _public prototype_ `void Add(const TSharedPtr<class ISkeletonTreeItem>& InItem, const FName& InParentName, const FName& InParentType, bool bAddToHead = false);` — Add an item to the output @param	InItem			The item to add @param	InParentName	The name of the item's parent @param	InParentType	The type of items to search. If this is NAME_None all items will be searched. @param	bAddToHead		Whether to add the item to the start or end of the parent's children array
- L59 _public prototype_ `TSharedPtr<class ISkeletonTreeItem> Find(const FName& InName, TArrayView<const FName> InTypes) const;` — Find the item with the specified name @param	InName	The item's name @param	InTypes	The types of items to search. If this is empty all items will be searched. @return the item found, or an invalid ptr if it was not found.
- L67 _public function_ `FORCEINLINE TSharedPtr<class ISkeletonTreeItem> Find(const FName& InName, std::initializer_list<FName> InTypes) const` — Find the item with the specified name @param	InName	The item's name @param	InTypes	The types of items to search. If this is empty all items will be searched. @return the item found, or an invalid ptr if it was not found.
- L78 _public prototype_ `TSharedPtr<class ISkeletonTreeItem> Find(const FName& InName, const FName& InType) const;` — Find the item with the specified name @param	InName	The item's name @param	InType	The type of items to search. If this is NAME_None all items will be searched. @return the item found, or an invalid ptr if it was not found.
- L82 _private member_ `TArray<TSharedPtr<class ISkeletonTreeItem>>& Items;` — The items that are built by this builder
- L85 _private member_ `TArray<TSharedPtr<class ISkeletonTreeItem>>& LinearItems;` — A linearized list of all items in OutItems (for easier searching)

#### struct `FSkeletonTreeFilterArgs`  
`struct FSkeletonTreeFilterArgs`  
_L89-101_
- desc: Basic filter used when re-filtering the tree
- L91 _public function_ `FSkeletonTreeFilterArgs(TSharedPtr<FTextFilterExpressionEvaluator> InTextFilter) : TextFilter(InTextFilter) , bFlattenHierarchyOnFilter(true)`
- L97 _public member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;` — The text filter we are using, if any
- L100 _public member_ `bool bFlattenHierarchyOnFilter;` — Whether to flatten the hierarchy so filtered items appear in a linear list

#### class `ISkeletonTreeBuilder`  
`class ISkeletonTreeBuilder : public TSharedFromThis<ISkeletonTreeBuilder>`  
_L107-136_
- inherits: `TSharedFromThis<ISkeletonTreeBuilder>`
- desc: Interface to implement to provide custom build logic to skeleton trees
- L111 _public prototype_ `virtual ~ISkeletonTreeBuilder() = default;`
- L114 _public prototype_ `virtual void Initialize(const TSharedRef<class ISkeletonTree>& InSkeletonTree, const TSharedPtr<class IPersonaPreviewScene>& InPreviewScene, FOnFilterSkeletonTreeItem InOnFilterSkeletonTreeItem) = 0;` — Setup this builder with links to the tree and preview scene
- L120 _public prototype_ `virtual void Build(FSkeletonTreeBuilderOutput& Output) = 0;` — Build an array of skeleton tree items to display in the tree. @param	Output			The items that are built by this builder
- L123 _public prototype_ `virtual void Filter(const FSkeletonTreeFilterArgs& InArgs, const TArray<TSharedPtr<class ISkeletonTreeItem>>& InItems, TArray<TSharedPtr<class ISkeletonTreeItem>>& OutFilteredItems) = 0;` — Apply filtering to the tree items
- L126 _public prototype_ `virtual ESkeletonTreeFilterResult FilterItem(const FSkeletonTreeFilterArgs& InArgs, const TSharedPtr<class ISkeletonTreeItem>& InItem) = 0;` — Allows the builder to contribute to filtering an item
- L129 _public prototype_ `virtual bool IsShowingBones() const = 0;` — Get whether this builder is showing bones
- L132 _public prototype_ `virtual bool IsShowingSockets() const = 0;` — Get whether this builder is showing bones
- L135 _public prototype_ `virtual bool IsShowingAttachedAssets() const = 0;` — Get whether this builder is showing bones

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SKELETONEDITOR_API`
- L104 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(ESkeletonTreeFilterResult, FOnFilterSkeletonTreeItem, const FSkeletonTreeFilterArgs& , const TSharedPtr<class ISkeletonTreeItem>& );` — Delegate used to filter an item.
- L104 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(ESkeletonTreeFilterResult, FOnFilterSkeletonTreeItem, const FSkeletonTreeFilterArgs& , const TSharedPtr<class ISkeletonTreeItem>& );` — Delegate used to filter an item.

### `Source/Editor/SkeletonEditor/Public/ISkeletonTreeItem.h` (Public)


#### enum `ESkeletonTreeFilterResult`  
`enum class ESkeletonTreeFilterResult : int32`  
_L16-29_
- desc: Order is important here! This enum is used internally to the filtering logic and represents an ordering of most filtered (hidden) to least filtered (highlighted).
- L19 _public enumerator_ `Hidden` — Hide the item
- L22 _public enumerator_ `ShownDescendant` — Show the item because child items were shown
- L25 _public enumerator_ `Shown` — Show the item
- L28 _public enumerator_ `ShownHighlighted` — Show the item and highlight search text

#### class `ISkeletonTreeItem`  
`class ISkeletonTreeItem : public TSharedFromThis<ISkeletonTreeItem>`  
_L37-124_
- inherits: `TSharedFromThis<ISkeletonTreeItem>`
- desc: Interface for a skeleton tree item
- L40 _public function_ `SKELETON_TREE_BASE_ITEM_TYPE(ISkeletonTreeItem) template<typename TType> bool IsOfType() const`
- L48 _public prototype_ `virtual ~ISkeletonTreeItem() = default;`
- L51 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, const TAttribute<FText>& InFilterText) = 0;` — Builds the table row widget to display this info
- L54 _public prototype_ `virtual void GenerateWidgetForNameColumn(TSharedPtr< SHorizontalBox > Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) = 0;` — Builds the slate widget for the name column
- L57 _public prototype_ `virtual TSharedRef< SWidget > GenerateWidgetForDataColumn(const FName& DataColumnName, FIsSelected InIsSelected) = 0;` — Builds the slate widget for the data column
- L60 _public prototype_ `virtual TSharedRef< SWidget > GenerateInlineEditWidget(const TAttribute<FText>& FilterText, FIsSelected InIsSelected) = 0;` — Builds the slate widget for any inline data editing
- L63 _public prototype_ `virtual bool HasInlineEditor() const = 0;` — @return true if the item has an in-line editor widget
- L66 _public prototype_ `virtual void ToggleInlineEditorExpansion() = 0;` — Toggle the expansion state of the inline editor
- L69 _public prototype_ `virtual bool IsInlineEditorExpanded() const = 0;` — Get the expansion state of the inline editor
- L72 _public prototype_ `virtual FName GetRowItemName() const = 0;` — Get the name of the item that this row represents
- L75 _public prototype_ `virtual FName GetAttachName() const = 0;` — Return the name used to attach to this item
- L78 _public prototype_ `virtual bool CanRenameItem() const = 0;` — @return true if this item can be renamed
- L81 _public prototype_ `virtual void RequestRename() = 0;` — Requests a rename on the the tree row item
- L84 _public prototype_ `virtual void OnItemDoubleClicked() = 0;` — Handler for when the user double clicks on this item in the tree
- L87 _public prototype_ `virtual void HandleDragEnter(const FDragDropEvent& DragDropEvent) = 0;` — Handle a drag and drop enter event
- L90 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) = 0;` — Handle a drag and drop leave event
- L93 _public prototype_ `virtual FReply HandleDrop(const FDragDropEvent& DragDropEvent) = 0;` — Handle a drag and drop drop event
- L96 _public prototype_ `virtual TSharedPtr<ISkeletonTreeItem> GetParent() const = 0;` — Get this item's parent
- L99 _public prototype_ `virtual void SetParent(TSharedPtr<ISkeletonTreeItem> InParent) = 0;` — Set this item's parent
- L102 _public prototype_ `virtual TArray<TSharedPtr<ISkeletonTreeItem>>& GetChildren() = 0;` — The array of children for this item
- L105 _public prototype_ `virtual TArray<TSharedPtr<ISkeletonTreeItem>>& GetFilteredChildren() = 0;` — The filtered array of children for this item
- L108 _public prototype_ `virtual TSharedRef<class ISkeletonTree> GetSkeletonTree() const = 0;` — The owning skeleton tree
- L111 _public prototype_ `virtual TSharedRef<class IEditableSkeleton> GetEditableSkeleton() const = 0;` — Get the editable skeleton the tree represents
- L114 _public prototype_ `virtual ESkeletonTreeFilterResult GetFilterResult() const = 0;` — Get the current filter result
- L117 _public prototype_ `virtual void SetFilterResult(ESkeletonTreeFilterResult InResult) = 0;` — Set the current filter result
- L120 _public prototype_ `virtual UObject* GetObject() const = 0;` — Get the object represented by this item, if any
- L123 _public prototype_ `virtual bool IsInitiallyExpanded() const = 0;` — Get whether this item begins expanded or not

#### Free symbols / members of external scopes

- L31 _macro_ `#define SKELETON_TREE_BASE_ITEM_TYPE(TYPE) \`
- L136 _macro_ `#define SKELETON_TREE_ITEM_TYPE(TYPE, BASE) \` — All concrete ISkeletonTreeItem-derived classes must include this macro. Example Usage: class FMyTreeItem : public ISkeletonTreeItem { public: SKELETON_TREE_ITEM_TYPE(FMyTreeItem, ISkeletonTreeItem) ... };

### `Source/Editor/SkeletonEditor/Public/SkeletonToolMenuContext.h` (Public)


#### class `USkeletonToolMenuContext`  
`class USkeletonToolMenuContext : public UObject`  
_L12-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L17 _public member_ `TWeakPtr<ISkeletonEditor> SkeletonEditor;`

### `Source/Editor/SkeletonEditor/Public/SkeletonTreeBuilder.h` (Public)


#### struct `FSkeletonTreeBuilderArgs`  
`struct FSkeletonTreeBuilderArgs`  
_L17-37_
- desc: Options for skeleton building
- L19 _public function_ `FSkeletonTreeBuilderArgs(bool bInShowBones = true, bool bInShowSockets = true, bool bInShowAttachedAssets = true, bool bInShowVirtualBones = true) : bShowBones(bInShowBones) , bShowSockets(bInShowSockets) , bShowAttachedAssets(bInShowAttachedAssets) , bShowVirtualBones(bInShowVirtualBones)`
- L27 _public member_ `bool bShowBones;` — Whether we should show bones
- L30 _public member_ `bool bShowSockets;` — Whether we should show sockets
- L33 _public member_ `bool bShowAttachedAssets;` — Whether we should show attached assets
- L36 _public member_ `bool bShowVirtualBones;` — Whether we should show virtual bones

#### enum `EBoneFilter`  
`enum class EBoneFilter : int32`  
_L40-48_
- desc: Enum which tells us what type of bones we should be showing
- L42 _public enumerator_ `All`
- L43 _public enumerator_ `Mesh`
- L44 _public enumerator_ `LOD`
- L45 _public enumerator_ `Weighted`
- L46 _public enumerator_ `None` — Weighted,   only showing weighted bones of current LOD
- L47 _public enumerator_ `Count`

#### enum `ESocketFilter`  
`enum class ESocketFilter : int32`  
_L51-59_
- desc: Enum which tells us what type of sockets we should be showing
- L53 _public enumerator_ `Active`
- L54 _public enumerator_ `Mesh`
- L55 _public enumerator_ `Skeleton`
- L56 _public enumerator_ `All`
- L57 _public enumerator_ `None`
- L58 _public enumerator_ `Count`

#### class `FSkeletonTreeBuilder`  
`class FSkeletonTreeBuilder : public ISkeletonTreeBuilder`  
_L61-120_
- inherits: `ISkeletonTreeBuilder`
- L64 _public prototype_ `FSkeletonTreeBuilder(const FSkeletonTreeBuilderArgs& InBuilderArgs);`
- L67 _public prototype_ `virtual void Initialize(const TSharedRef<class ISkeletonTree>& InSkeletonTree, const TSharedPtr<class IPersonaPreviewScene>& InPreviewScene, FOnFilterSkeletonTreeItem InOnFilterSkeletonTreeItem) override;` — ISkeletonTreeBuilder interface
- L68 _public prototype_ `virtual void Build(FSkeletonTreeBuilderOutput& Output) override;`
- L69 _public prototype_ `virtual void Filter(const FSkeletonTreeFilterArgs& InArgs, const TArray<TSharedPtr<class ISkeletonTreeItem>>& InItems, TArray<TSharedPtr<class ISkeletonTreeItem>>& OutFilteredItems) override;`
- L70 _public prototype_ `virtual ESkeletonTreeFilterResult FilterItem(const FSkeletonTreeFilterArgs& InArgs, const TSharedPtr<class ISkeletonTreeItem>& InItem) override;`
- L71 _public prototype_ `virtual bool IsShowingBones() const override;`
- L72 _public prototype_ `virtual bool IsShowingSockets() const override;`
- L73 _public prototype_ `virtual bool IsShowingAttachedAssets() const override;`
- L77 _protected prototype_ `void AddBones(FSkeletonTreeBuilderOutput& Output);` — Add Bones
- L80 _protected prototype_ `void AddSockets(FSkeletonTreeBuilderOutput& Output);` — Add Sockets
- L82 _protected prototype_ `void AddAttachedAssets(FSkeletonTreeBuilderOutput& Output);`
- L84 _protected prototype_ `void AddSocketsFromData(const TArray< USkeletalMeshSocket* >& SocketArray, ESocketParentType ParentType, FSkeletonTreeBuilderOutput& Output);`
- L86 _protected prototype_ `void AddAttachedAssetContainer(const FPreviewAssetAttachContainer& AttachedObjects, FSkeletonTreeBuilderOutput& Output);`
- L88 _protected prototype_ `void AddVirtualBones(FSkeletonTreeBuilderOutput& Output);`
- L91 _protected prototype_ `TSharedRef<class ISkeletonTreeItem> CreateBoneTreeItem(const FName& InBoneName);` — Create an item for a bone
- L94 _protected prototype_ `TSharedRef<class ISkeletonTreeItem> CreateSocketTreeItem(USkeletalMeshSocket* InSocket, ESocketParentType ParentType, bool bIsCustomized);` — Create an item for a socket
- L97 _protected prototype_ `TSharedRef<class ISkeletonTreeItem> CreateAttachedAssetTreeItem(UObject* InAsset, const FName& InAttachedTo);` — Create an item for an attached asset
- L100 _protected prototype_ `TSharedRef<class ISkeletonTreeItem> CreateVirtualBoneTreeItem(const FName& InBoneName);` — Create an item for a virtual bone
- L103 _protected prototype_ `ESkeletonTreeFilterResult FilterRecursive(const FSkeletonTreeFilterArgs& InArgs, const TSharedPtr<ISkeletonTreeItem>& InItem, TArray<TSharedPtr<ISkeletonTreeItem>>& OutFilteredItems);` — Helper function for filtering
- L107 _protected member_ `FSkeletonTreeBuilderArgs BuilderArgs;` — Options for building
- L110 _protected member_ `FOnFilterSkeletonTreeItem OnFilterSkeletonTreeItem;` — Delegate used for filtering
- L113 _protected member_ `TWeakPtr<class ISkeletonTree> SkeletonTreePtr;` — The skeleton tree we will build against
- L116 _protected member_ `TWeakPtr<class IEditableSkeleton> EditableSkeletonPtr;` — The editable skeleton that the skeleton tree represents
- L119 _protected member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — The (optional) preview scene we will build against

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SKELETONEDITOR_API`

### `Source/Editor/SkeletonEditor/Public/SkeletonTreeItem.h` (Public)


#### class `FSkeletonTreeItem`  
`class FSkeletonTreeItem : public ISkeletonTreeItem`  
_L31-84_
- inherits: `ISkeletonTreeItem`
- desc: Provides basic stub functionality for ISkeletonTreeItem-derived classes
- L38 _public function_ `FSkeletonTreeItem(const TSharedRef<class ISkeletonTree>& InSkeletonTree) : SkeletonTreePtr(InSkeletonTree) , FilterResult(ESkeletonTreeFilterResult::Shown)`
- L44 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, const TAttribute<FText>& InFilterText) override;` — ISkeletonTreeItem interface
- L45 _public function_ `virtual TSharedRef< SWidget > GenerateWidgetForDataColumn(const FName& DataColumnName, FIsSelected InIsSelected) override`
- L46 _public function_ `virtual TSharedRef< SWidget > GenerateInlineEditWidget(const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override`
- L47 _public function_ `virtual bool HasInlineEditor() const override`
- L48 _public function_ `virtual void ToggleInlineEditorExpansion() override`
- L49 _public function_ `virtual bool IsInlineEditorExpanded() const override`
- L50 _public function_ `virtual FName GetAttachName() const override`
- L51 _public function_ `virtual bool CanRenameItem() const override`
- L52 _public function_ `virtual void RequestRename() override`
- L53 _public function_ `virtual void OnItemDoubleClicked() override`
- L54 _public function_ `virtual void HandleDragEnter(const FDragDropEvent& DragDropEvent) override`
- L55 _public function_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) override`
- L56 _public function_ `virtual FReply HandleDrop(const FDragDropEvent& DragDropEvent) override`
- L57 _public function_ `virtual TSharedPtr<ISkeletonTreeItem> GetParent() const override`
- L58 _public function_ `virtual void SetParent(TSharedPtr<ISkeletonTreeItem> InParent) override`
- L59 _public function_ `virtual TArray<TSharedPtr<ISkeletonTreeItem>>& GetChildren() override`
- L60 _public function_ `virtual TArray<TSharedPtr<ISkeletonTreeItem>>& GetFilteredChildren() override`
- L61 _public function_ `virtual TSharedRef<class ISkeletonTree> GetSkeletonTree() const override`
- L62 _public function_ `virtual TSharedRef<class IEditableSkeleton> GetEditableSkeleton() const override`
- L63 _public function_ `virtual ESkeletonTreeFilterResult GetFilterResult() const override`
- L64 _public function_ `virtual void SetFilterResult(ESkeletonTreeFilterResult InResult) override`
- L65 _public function_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L66 _public function_ `virtual UObject* GetObject() const override`
- L67 _public function_ `virtual bool IsInitiallyExpanded() const override`
- L71 _protected member_ `TWeakPtr<ISkeletonTreeItem> Parent;` — The parent of this item
- L74 _protected member_ `TArray<TSharedPtr<ISkeletonTreeItem>> Children;` — The children of this item
- L77 _protected member_ `TArray<TSharedPtr<ISkeletonTreeItem>> FilteredChildren;` — The filtered children of this item
- L80 _protected member_ `TWeakPtr<class ISkeletonTree> SkeletonTreePtr;` — The owning skeleton tree
- L83 _protected member_ `ESkeletonTreeFilterResult FilterResult;` — The current filter result

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API SKELETONEDITOR_API`

### `Source/Editor/SkeletonEditor/Public/SkeletonTreeSelection.h` (Public)


#### class `FSkeletonTreeSelection`  
`class FSkeletonTreeSelection`  
_L10-133_
- desc: Helper for processing tree selections
- L14 _public member_ `TArrayView<TSharedPtr<ISkeletonTreeItem>> SelectedItems;` — Flat array of selected items
- L16 _public function_ `FSkeletonTreeSelection(TArray<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems) : SelectedItems(InSelectedItems)`
- L21 _public function_ `FSkeletonTreeSelection(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems) : SelectedItems(InSelectedItems)`
- L26 _public function_ `bool IsMultipleItemsSelected() const`
- L31 _public function_ `bool IsSingleItemSelected() const`
- L37 _public function_ `template<typename ItemType> bool IsSingleOfTypeSelected() const`
- L47 _public function_ `template<typename... ItemTypes> bool IsSingleOfTypesSelected() const`
- L57 _public function_ `TSharedPtr<ISkeletonTreeItem> GetSingleSelectedItem()`
- L64 _public function_ `template<typename ItemType> bool HasSelectedOfType() const`
- L78 _public function_ `template<typename... ItemTypes> bool HasSelectedOfTypes() const`
- L93 _public function_ `template<typename ItemType> TArray<TSharedPtr<ItemType>> GetSelectedItems() const`
- L107 _public function_ `template<typename... ItemTypes> TArray<TSharedPtr<ISkeletonTreeItem>> GetSelectedItemsOfTypes() const`
- L121 _public function_ `TArray<TSharedPtr<ISkeletonTreeItem>> GetSelectedItemsByTypeId(const FName& InTypeId) const`
