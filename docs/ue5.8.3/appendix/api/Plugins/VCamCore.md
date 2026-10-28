# Plugins / VCamCore

- module root: `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore`
- headers: 61; symbols: 967
- symbol kinds: class=42, delegate=19, enum=11, enumerator=35, externvar=1, function=142, member=216, namespace=60, prototype=403, struct=36, typedef=2
- PrivateDependencyModuleNames: Concert, ConcertSyncClient, CoreUObject, EditorFramework, Engine, GameplayTags, InputCore, InputEditor, LevelEditor, MediaIOCore, MultiUserClient, Projects, RenderCore, Slate, SlateCore, UMG, UnrealEd, VPRoles, VPSettings, ViewportWidgetOverlay
- PublicDependencyModuleNames: ApplicationCore, CinematicCamera, Core, DeveloperSettings, EnhancedInput, LiveLinkInterface, RemoteSession, VPUtilities, ViewportWidgetOverlay

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Input/VCamInputProcessor.h` (Private)


#### class `UE::VCamCore::FVCamInputProcessor`  
`class FVCamInputProcessor : public IInputProcessor`  
_L20-58_
- inherits: `IInputProcessor`
- desc: Passes inputs to UVCamPlayerInput::InputKey. This code is a modified version of FEnhancedInputEditorProcessor; the only difference is where the input ends up getting sent to.
- L24 _public prototype_ `FVCamInputProcessor(UInputVCamSubsystem& OwningSubsystem);`
- L27 _public prototype_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;`
- L28 _public prototype_ `virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L29 _public prototype_ `virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L30 _public prototype_ `virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent) override;`
- L31 _public prototype_ `virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L32 _public prototype_ `virtual bool HandleMouseButtonDownEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L33 _public prototype_ `virtual bool HandleMouseButtonUpEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L34 _public prototype_ `virtual bool HandleMouseButtonDoubleClickEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L35 _public prototype_ `virtual bool HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent) override;`
- L36 _public function_ `virtual const TCHAR* GetDebugName() const`
- L41 _private member_ `TWeakObjectPtr<UInputVCamSubsystem> OwningSubsystem;`
- L47 _private member_ `FIntPoint NumCursorSamplesThisFrame = FIntPoint::ZeroValue;` — The number of cursor samples that happened this frame. The X and Y will be incremented when there is a mouse move event this frame and it will be reset on ProcessAccumulatedPointerInput.
- L50 _private member_ `FVector2D CachedCursorDelta = FVector2D::ZeroVector;` — The value of the mouse cursor from the most recent mouse event
- L52 _private prototype_ `void UpdateCachedPointerPosition(const FPointerEvent& MouseEvent);`
- L54 _private prototype_ `void ProcessAccumulatedPointerInput(float DeltaTime);` — Called on Tick to process any accumulated mouse input
- L57 _private prototype_ `bool InputKeyToSubsystem(const FInputKeyEventArgs& Params);` — Tells the Enhanced Input Editor subsystem about the given key event

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/LogVCamCore.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamCore, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamCore, Log, All);`
- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamInputDebug, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamInputDebug, Log, All);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/BlueprintUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace VCamCore` (scope `UE`)
- L11 _prototype_ `bool CanInitVCamInstance(UVCamComponent* Component);` (scope `UE::VCamCore`) — @return Whether the given VCamComponent is allowed to be initialized (e.g. cannot be if is in a Blueprint world)
- L13 _prototype_ `bool CanInitVCamOutputProvider(UVCamOutputProviderBase* OutputProvider);` (scope `UE::VCamCore`) — @return Whether the given VCamComponent is allowed to be initialized (e.g. cannot be if is in a Blueprint world)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/CookingUtils.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace VCamCore` (scope `UE`)
- L16 _namespace_ `namespace CookingUtils` (scope `UE::VCamCore`)
- L20 _prototype_ `void RemoveUnsupportedOutputProviders(TArray<TObjectPtr<UVCamOutputProviderBase>>& OutputProviders, const FObjectPreSaveContext& SaveContext);` (scope `UE::VCamCore::CookingUtils`) — Removes every entry that is either 1. null or 2. does not satisfy CanIncludeInCookedGame.
- L23 _prototype_ `void RemoveUnsupportedModifiers(TArray<FModifierStackEntry>& OutputProviders, const FObjectPreSaveContext& SaveContext);` (scope `UE::VCamCore::CookingUtils`) — Removes every entry that is either 1. null or 2. does not satisfy CanIncludeInCookedGame.
- L36 _prototype_ `bool CanIncludeInCookedGame(UObject& Object, const FObjectPreSaveContext& SaveContext);` (scope `UE::VCamCore::CookingUtils`) — Determines whether it is safe to package this object, which is usually a UVCamOutputProvider or UVCamModifier. This function does two things: - Check whether Object returns true from IsEditorOnly() (optimization) - Check whether the first native (parent) class is in a runtime module that supported by the target platform. Editor-only Blueprint UVCamModifiers can inherit from UEditorOnlyVCamModifier to be skipped. @return Whether to include this object in a build.

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/DeferredCleanupHandler.h` (Private)


#### class `UE::VCamCore::FDeferredCleanupHandler`  
`class FDeferredCleanupHandler : public FNoncopyable`  
_L25-52_
- inherits: `FNoncopyable`
- desc: This class is responsible for cleaning up any resources created by UVCamComponents that implement the FDeferredCleanupInterface. These resources are typically generated by user code, such as widgets, output providers, or modifiers. A common example of such a resource is a dynamic material instance used within a UUserWidget wrapped by SRetainerWidget. Without cleanup, the FRetainerWidgetRenderingResources within SRetainerWidget::RenderingResources continues referencing the material until the rendering thread cleans up the resources. When the editor world is destroyed, this leads to a fatal error during UEditorEngine::CheckForWorldGCLeaks. To prevent this, all UVCamComponents are deinitialized when FEditorSupportDelegates::PrepareToCleanseEditorObject is invoked, and any pending rendering commands are flushed when FEditorSupportDelegates::CleanseEditor is called.
- L29 _public prototype_ `FDeferredCleanupHandler();`
- L30 _public prototype_ `~FDeferredCleanupHandler();`
- L33 _public prototype_ `void OnInitializeVCam(UVCamComponent& Component);` — Starts tracking Component so its rendering resources are destroyed correctly.
- L35 _public prototype_ `void OnDeinitializeVCam(UVCamComponent& Component);` — Cleans up Component's rendering resources if needed and stops tracking it for clean-up.
- L42 _private member_ `TArray<TWeakObjectPtr<UVCamComponent>> KnownVCams;` — The VCams that may need cleaning up.
- L45 _private member_ `bool bNeedsFlush = false;` — Whether a flush of rendering resources should be triggered to ensure that any deferred rendering resources are cleaned up.
- L48 _private prototype_ `void OnPrepareToCleanseEditor(UObject* Object);` — Delegate into FEditorSupportDelegates::PrepareToCleanseEditorObject.
- L50 _private prototype_ `void OnCleanseEditor();` — Delegate into FEditorSupportDelegates::CleanseEditor.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/ObjectMessageAggregation.h` (Private)


#### struct `UE::VCamCore::FAggregatedNotification`  
`struct FAggregatedNotification`  
_L12-25_
- L15 _public member_ `FName Identifier;` — Messages are grouped by identifier.
- L21 _public member_ `FText Title;` — The title of the notification. It should be the same for all notifications with the same identifier for the same object, e.g. "Missing viewport 1"
- L24 _public member_ `FText Subtext;` — Specific data that is combined in the notification's subtext section.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace VCamCore` (scope `UE`)
- L28 _externvar_ `extern const FName NotificationKey_MissingTargetViewport;` (scope `UE::VCamCore`) — Output provider message displayed when the target viewport is not currently open in the UI.
- L41 _prototype_ `void AddAggregatedNotification(UObject& ContextObject, FAggregatedNotification Notification);` (scope `UE::VCamCore`) — Adds a notification. If compiling against the editor, a notification is added to the bottom-right of the screen. A log is generated regardless of compile target. The notification is logged immediately. To avoid UI spam, at the end of the frame, all notifications are aggregated per notification identifier. @param ContextObject The object for which this notification is generated. If multiple messages are received in the same frame, they are combined. @param Notification The notification about this object

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/Viewport/Interfaces/IViewportGetter.h` (Private)


#### class `UE::VCamCore::IViewportGetter`  
`class IViewportGetter`  
_L27-51_
- desc: Abstracts the viewport system. This interface only contains those functions required by FViewportManager, i.e. those that UVCamOutputProviderBase uses to query viewport information. This is implemented differently depending on the platform: - In editor, it uses the real viewport system (unless in PIE) - In PIE, it uses the player viewport (ignores the viewport ID) - In shipped applications, it uses the player viewport (ignores the viewport ID)
- L32 _public prototype_ `virtual TSharedPtr<FSceneViewport> GetSceneViewport(EVCamTargetViewportID ViewportID) const = 0;` — @return Gets the scene viewport that is identified by ViewportID.
- L35 _public prototype_ `virtual TWeakPtr<SWindow> GetInputWindow(EVCamTargetViewportID ViewportID) const = 0;` — @return The window which contains the viewport identified by ViewportID. Some output providers uses this to route input, e.g. pixel streaming.
- L47 _public function_ `virtual FLevelEditorViewportClient* GetEditorViewportClient(EVCamTargetViewportID ViewportID) const` — Gets the FLevelEditorViewportClient that is managing the ViewportID. This will only return valid in the editor environment (thus not work in PIE or games). If the UVCamOutputProviderBase::DisplayType is EVPWidgetDisplayType::PostProcessWithBlendMaterial, the FEditorViewportClient::ViewModifiers are used to overlay the widget into the viewport because it plays nicely with other viewports. In games, the output provider simply places the post process material in the target camera because there is only one viewport. Hence, there is no implementation for games.
- L50 _public prototype_ `virtual ~IViewportGetter() = default;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/Viewport/Interfaces/IViewportLocker.h` (Private)


#### struct `UE::VCamCore::FActorLockContext`  
`struct FActorLockContext`  
_L16-29_
- L25 _public member_ `UVCamOutputProviderBase* ProviderToLock;` — The output provider for which is being locked. Its outer actor will be locking the viewport. Can be used e.g. by the PIE implementation of IViewportLocker to ask the provider's UGameplayViewTargetPolicy to determine the APlayerController for which to change the viewport.
- L27 _public function_ `AActor* GetLockActor() const`
- L28 _public function_ `bool ShouldLock() const`

#### class `UE::VCamCore::IViewportLocker`  
`class IViewportLocker`  
_L42-58_
- desc: Abstracts the viewport system. This interface only contains the functions used by FViewportLockManager, i.e. those needed for viewport locking. This is implemented differently depending on the platform: - In editor, it uses the real viewport system (unless in PIE) - In PIE, it uses the player viewport (ignores the viewport ID) - In shipped applications, it uses the player viewport (ignores the viewport ID) This also allows mocking in tests.
- L47 _public prototype_ `virtual TWeakObjectPtr<AActor> GetActorLock(EVCamTargetViewportID ViewportID) const = 0;` — Gets the lock actor. See FLevelEditorViewportClient::GetActorLock
- L49 _public prototype_ `virtual TWeakObjectPtr<AActor> GetCinematicActorLock(EVCamTargetViewportID ViewportID) const = 0;` — Gets the cinematic lock actor. See FLevelEditorViewportClient::GetCinematicActorLock
- L52 _public prototype_ `virtual bool IsViewportLocked(EVCamTargetViewportID ViewportID) const = 0;` — Gets whether GetActorLock is being locked to the viewport. See FLevelEditorViewportClient::bLockedCameraView.
- L55 _public prototype_ `virtual void SetActorLock(EVCamTargetViewportID ViewportID, const FActorLockContext& LockInfo) = 0;` — Sets the lock actor.
- L57 _public prototype_ `virtual ~IViewportLocker() = default;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/Viewport/Interfaces/IViewportResolutionChanger.h` (Private)


#### class `UE::VCamCore::IViewportResolutionChanger`  
`class IViewportResolutionChanger`  
_L23-34_
- desc: Abstracts the viewport system. This interface only contains the functions used by FViewportResolutionManager, i.e. those needed for viewport resolution changing. This is implemented differently depending on the platform: - In editor, it uses the real viewport system (unless in PIE) - In PIE, it uses the player viewport (ignores the viewport ID) - In shipped applications, it uses the player viewport (ignores the viewport ID) This also allows mocking in tests.
- L28 _public prototype_ `virtual void ApplyOverrideResolutionForViewport(EVCamTargetViewportID ViewportID, uint32 NewViewportSizeX, uint32 NewViewportSizeY) = 0;` — Sets the override resolution of the given viewport. See FSceneViewport::SetFixedViewportSize.
- L31 _public prototype_ `virtual void RestoreOverrideResolutionForViewport(EVCamTargetViewportID ViewportID) = 0;` — Clears the resolution override of the given viewport. See FSceneViewport::SetFixedViewportSize
- L33 _public prototype_ `virtual ~IViewportResolutionChanger() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/Viewport/OwnershipMapping.h` (Private)


#### class `UE::VCamCore::TOwnershipMapping`  
`template<CThing TThing, COwner TOwner> class TOwnershipMapping`  
_L35-95_
- desc: Abstracts the concept of ownership. Multiple agents can try to take and release ownership over a thing. The first one to request it gains the owner. If another agent requests ownership over something that's already owned, then it will get ownership if the current owner releases ownership. @tparam TThing The type of the thing being owned @tparam TOwner The type of whatever owns the thing
- L39 _public function_ `~TOwnershipMapping()`
- L45 _public prototype_ `bool TryTakeOwnership(const TOwner& Owner, const TThing& Thing);` — Attemps to assign owner ship for Thing to Owner, or enqueues it. @return Whether Owner now has ownership over Thing.
- L48 _public function_ `void ReleaseOwnership(const TOwner& Owner)` — Releases Owner's ownership over all its registered things.
- L50 _public function_ `void ReleaseOwnership(const TOwner& Owner, const TThing& Thing)` — Releases Owner's ownership over Thing.
- L53 _public prototype_ `void Clear(bool bSilent = true);` — Clears all ownership.
- L56 _public prototype_ `const TOwner* GetOwner(const TThing& Thing) const;` — @return Gets the owner of Thing or nullptr.
- L58 _public function_ `bool IsOwnedBy(const TThing& Thing, const TOwner& TestOwner) const` — @return Whether Thing is owned by Owner.
- L60 _public function_ `bool HasOwner(const TThing& Thing) const` — @return Whether Thing has an Owner.
- L67 _public prototype_ `template<typename TLambda> requires std::is_invocable_r_v<bool, TLambda, const TOwner&> void RemovePotentialOwnerIf(const TThing& Thing, const TLambda& Callback);` — Removes every TOwner that has called TryTakeOwnership for Thing. The callback returns true if it wants to remove the object.
- L69 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOwnershipChanged, const TThing& Thing, const TOptional<TOwner> NewOwner);`
- L71 _public function_ `FOnOwnershipChanged& OnOwnershipChanged()` — Called when ownership changes for a thing.
- L83 _private member_ `TMap<TThing, FOwnershipData> Ownership;` — Stores the ownership state.
- L86 _private member_ `FOnOwnershipChanged OnOwnershipChangedDelegate;` — Called when ownership changes for a thing.
- L89 _private prototype_ `template<typename TRemoveLambda> void RemoveOwnershipSingle(const TOwner& Owner, const TThing& Thing, FOwnershipData* OwnershipData, const TRemoveLambda& RemoveLambda);`
- L90 _private function_ `void RemoveOwnershipSingle(const TOwner& Owner, const TThing& Thing)`
- L94 _private prototype_ `void RemoveOwnershipAll(const TOwner& Owner);`
- L98 _function_ `template <CThing TThing, COwner TOwner> bool TOwnershipMapping<TThing, TOwner>::TryTakeOwnership(const TOwner& Owner, const TThing& Thing)`
- L114 _function_ `template <CThing TThing, COwner TOwner> void TOwnershipMapping<TThing, TOwner>::Clear(bool bSilent)`
- L138 _function_ `template <CThing TThing, COwner TOwner> const TOwner* TOwnershipMapping<TThing, TOwner>::GetOwner(const TThing& Thing) const`
- L146 _function_ `template <CThing TThing, COwner TOwner> template <typename TLambda> requires std::is_invocable_r_v<bool, TLambda, const TOwner&> void TOwnershipMapping<TThing, TOwner>::RemovePotentialOwnerIf(const TThing& Thing, const TLambda& Callback)`
- L182 _function_ `template <CThing TThing, COwner TOwner> template <typename TRemoveLambda> void TOwnershipMapping<TThing, TOwner>::RemoveOwnershipSingle(const TOwner& Owner, const TThing& Thing, FOwnershipData* OwnershipData, const TRemoveLambda& RemoveLambda)`
- L203 _function_ `template <CThing TThing, COwner TOwner> void TOwnershipMapping<TThing, TOwner>::RemoveOwnershipAll(const TOwner& Owner)`

#### struct `UE::VCamCore::TOwnershipMapping::FOwnershipData`  
`struct FOwnershipData`  
_L75-81_
- L78 _public member_ `TArray<TOwner> OwnershipPriority;` — Sorted by the order in which ownership was registered.
- L80 _public function_ `const TOwner* GetOwner() const`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace VCamCore` (scope `UE`)
- L69 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOwnershipChanged, const TThing& Thing, const TOptional<TOwner> NewOwner);`
- L92 _function_ `RemoveOwnershipSingle(Owner, Thing, Ownership.Find(Thing), [this, &Thing](){ Ownership.Remove(Thing); });` (scope `UE::VCamCore::TOwnershipMapping::RemoveOwnershipSingle`)
- L208 _function_ `` (scope `UE::VCamCore::TOwnershipMapping::RemoveOwnershipAll`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/Viewport/Systems/EditorViewportSystem.h` (Private)


#### class `UE::VCamCore::FEditorViewportSystem`  
`class FEditorViewportSystem : public IViewportLocker , public IViewportResolutionChanger , public IViewportGetter`  
_L13-45_
- inherits: `IViewportLocker,IViewportResolutionChanger,IViewportGetter`
- desc: Uses the editor's multiple viewports.
- L21 _public prototype_ `virtual TWeakObjectPtr<AActor> GetActorLock(EVCamTargetViewportID ViewportID) const override;`
- L22 _public prototype_ `virtual TWeakObjectPtr<AActor> GetCinematicActorLock(EVCamTargetViewportID ViewportID) const override;`
- L23 _public prototype_ `virtual bool IsViewportLocked(EVCamTargetViewportID ViewportID) const override;`
- L24 _public prototype_ `virtual void SetActorLock(EVCamTargetViewportID ViewportID, const FActorLockContext& LockInfo) override;`
- L28 _public prototype_ `virtual void ApplyOverrideResolutionForViewport(EVCamTargetViewportID ViewportID, uint32 NewViewportSizeX, uint32 NewViewportSizeY) override;`
- L29 _public prototype_ `virtual void RestoreOverrideResolutionForViewport(EVCamTargetViewportID ViewportID) override;`
- L33 _public prototype_ `virtual TSharedPtr<FSceneViewport> GetSceneViewport(EVCamTargetViewportID ViewportID) const override;`
- L34 _public prototype_ `virtual TWeakPtr<SWindow> GetInputWindow(EVCamTargetViewportID ViewportID) const override;`
- L35 _public prototype_ `virtual FLevelEditorViewportClient* GetEditorViewportClient(EVCamTargetViewportID ViewportID) const override;`
- L44 _private member_ `FViewportRestoreData RestoreData[static_cast<int32>(EVCamTargetViewportID::Count)];`

#### struct `UE::VCamCore::FEditorViewportSystem::FViewportRestoreData`  
`struct FViewportRestoreData`  
_L40-43_
- L42 _public member_ `float OldViewFov = 90.f;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/Viewport/Systems/GameViewportSystem.h` (Private)


#### class `UE::VCamCore::FGameViewportSystem`  
`class FGameViewportSystem : public IViewportLocker , public IViewportResolutionChanger , public IViewportGetter`  
_L14-50_
- inherits: `IViewportLocker,IViewportResolutionChanger,IViewportGetter`
- desc: Uses the editor's multiple viewports.
- L22 _public prototype_ `virtual TWeakObjectPtr<AActor> GetActorLock(EVCamTargetViewportID ViewportID) const override;`
- L23 _public function_ `virtual TWeakObjectPtr<AActor> GetCinematicActorLock(EVCamTargetViewportID ViewportID) const override`
- L24 _public prototype_ `virtual bool IsViewportLocked(EVCamTargetViewportID ViewportID) const override;`
- L25 _public prototype_ `virtual void SetActorLock(EVCamTargetViewportID ViewportID, const FActorLockContext& Context) override;`
- L29 _public prototype_ `virtual void ApplyOverrideResolutionForViewport(EVCamTargetViewportID ViewportID, uint32 NewViewportSizeX, uint32 NewViewportSizeY) override;`
- L30 _public prototype_ `virtual void RestoreOverrideResolutionForViewport(EVCamTargetViewportID ViewportID) override;`
- L34 _public prototype_ `virtual TSharedPtr<FSceneViewport> GetSceneViewport(EVCamTargetViewportID ViewportID) const override;`
- L35 _public prototype_ `virtual TWeakPtr<SWindow> GetInputWindow(EVCamTargetViewportID ViewportID) const override;`
- L46 _private member_ `TMap<EVCamTargetViewportID, FLockInfo> LockInfos;`
- L48 _private prototype_ `void TakeActorLock(EVCamTargetViewportID ViewportID, const FActorLockContext& Context);`
- L49 _private prototype_ `void ReleaseViewTarget(EVCamTargetViewportID ViewportID);`

#### struct `UE::VCamCore::FGameViewportSystem::FLockInfo`  
`struct FLockInfo`  
_L40-44_
- L42 _public member_ `TArray<TWeakObjectPtr<APlayerController>> PlayersWhoseViewTargetWasSet;`
- L43 _public member_ `TWeakObjectPtr<UVCamOutputProviderBase> LockProvider;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/Viewport/Systems/ViewportSystemSwitcher.h` (Private)


#### class `UE::VCamCore::FViewportSystemSwitcher`  
`class FViewportSystemSwitcher : public IViewportLocker , public IViewportResolutionChanger , public IViewportGetter`  
_L23-90_
- inherits: `IViewportLocker,IViewportResolutionChanger,IViewportGetter`
- desc: Switches between systems depending on whether we're in PIE or not. Depending on the platform, this uses a different system. - In shipped applications, it uses the player viewport (ignores the viewport ID) - In PIE, it uses the player viewport (ignores the viewport ID) - In editor, it uses the real viewport system (unless in PIE)
- L31 _public function_ `virtual TWeakObjectPtr<AActor> GetActorLock(EVCamTargetViewportID ViewportID) const override`
- L32 _public function_ `virtual TWeakObjectPtr<AActor> GetCinematicActorLock(EVCamTargetViewportID ViewportID) const override`
- L33 _public function_ `virtual bool IsViewportLocked(EVCamTargetViewportID ViewportID) const override`
- L34 _public function_ `virtual void SetActorLock(EVCamTargetViewportID ViewportID, const FActorLockContext& LockInfo) override`
- L38 _public function_ `virtual void ApplyOverrideResolutionForViewport(EVCamTargetViewportID ViewportID, uint32 NewViewportSizeX, uint32 NewViewportSizeY) override`
- L39 _public function_ `virtual void RestoreOverrideResolutionForViewport(EVCamTargetViewportID ViewportID) override`
- L43 _public function_ `virtual TSharedPtr<FSceneViewport> GetSceneViewport(EVCamTargetViewportID ViewportID) const override`
- L44 _public function_ `virtual TWeakPtr<SWindow> GetInputWindow(EVCamTargetViewportID ViewportID) const override`
- L46 _public function_ `virtual FLevelEditorViewportClient* GetEditorViewportClient(EVCamTargetViewportID ViewportID) const override`
- L53 _private member_ `FEditorViewportSystem EditorSystem;`
- L55 _private member_ `FGameViewportSystem GameSystem;`
- L57 _private function_ `const IViewportLocker& GetViewportLocker() const`
- L58 _private function_ `IViewportLocker& GetViewportLocker()`
- L59 _private function_ `const IViewportResolutionChanger& GetResolutionChanger() const`
- L60 _private function_ `IViewportResolutionChanger& GetResolutionChanger()`
- L61 _private function_ `const IViewportGetter& GetViewportGetter() const`
- L62 _private function_ `IViewportGetter& GetViewportGetter()`
- L65 _private function_ `template<typename T> const T& GetInterface() const`
- L71 _private function_ `template<typename T> T& GetInterface()`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace VCamCore` (scope `UE`)
- L81 _function_ `` (scope `UE::VCamCore::FViewportSystemSwitcher::GetInterface`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/Viewport/ViewportLockManager.h` (Private)


#### class `UE::VCamCore::FViewportLockManager`  
`class FViewportLockManager : public FNoncopyable`  
_L23-77_
- inherits: `FNoncopyable`
- desc: Uses UVCamComponent's lock settings for locking the editor or game viewport.
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FHasViewportOwnership, const UVCamOutputProviderBase&);`
- L29 _public prototype_ `FViewportLockManager( IViewportLocker& ViewportLocker UE_LIFETIMEBOUND, FHasViewportOwnership HasViewportOwnershipDelegate );`
- L35 _public prototype_ `void UpdateViewportLockState(TConstArrayView<TWeakObjectPtr<UVCamComponent>> RegisteredVCams);` — Checks which of the output providers in the given VCam array should lock the viewport.
- L38 _public prototype_ `bool WantsToLockViewportTo(const UVCamOutputProviderBase& OutputProvider) const;` — @return Whether the viewport should be locked to this OutputProvider.
- L43 _private member_ `IViewportLocker& ViewportLocker;` — Used to lock the viewport(s).
- L46 _private member_ `const FHasViewportOwnership HasViewportOwnershipDelegate;` — Looks up whether the given output provider has ownership over the viewport.
- L49 _private member_ `bool bRequestedRefresh = false;` — Whether to update the viewport locks at the end of the frame.
- L69 _private member_ `} LockState[4];`
- L71 _private prototype_ `FViewportLockState& GetLockState(EVCamTargetViewportID ViewportID);`
- L74 _private prototype_ `void UpdateViewport(TConstArrayView<TWeakObjectPtr<UVCamComponent>> RegisteredVCams, EVCamTargetViewportID ViewportID);` — Updates the viewport lock given the registered VCams.
- L76 _private prototype_ `void ClearActorLock(EVCamTargetViewportID ViewportID, FViewportLockState& LockInfo);` — Takes away the viewport from an output provider assigned to ViewportID.

#### struct `UE::VCamCore::FViewportLockManager::FViewportLockState`  
`struct FViewportLockState`  
_L51-69_
- L53 _public member_ `TWeakObjectPtr<const UVCamOutputProviderBase> LockReason;`
- L55 _public member_ `TWeakObjectPtr<const AActor> OwningActor;` — The actor that owns LockReason. Set together with LockReason.
- L57 _public function_ `void SetLockReason(const UVCamOutputProviderBase& InLockReason, const AActor& InOwningActor)`
- L64 _public function_ `void Reset()`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace VCamCore` (scope `UE`)
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FHasViewportOwnership, const UVCamOutputProviderBase&);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/Viewport/ViewportManager.h` (Private)


#### class `UE::VCamCore::FViewportManagerBase`  
`class FViewportManagerBase : public FNoncopyable`  
_L31-117_
- inherits: `FNoncopyable`
- desc: Decides the ownership of viewports for multiple output providers. Ownership is then passed to FViewportLockManager and FViewportResolutionManager, which handle locking the viewport and applying override resolution. An output provider has ownership over a viewport when: 1. Output provider is outputting 2. Owning UVCamComponent::ViewportLocker is configured to lock OR UVCamOutputProviderBase::NeedsForceLockToViewport. The specific implementations are designed to be injected; this allows unit tests to inject mocks.
- L36 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<bool>, FOverrideShouldHaveOwnership, const UVCamOutputProviderBase&);` — @return If set, the ownership is overriden with this value. If unset, the default behaviour is used.
- L43 _public prototype_ `FViewportManagerBase( IViewportLocker& ViewportLocker UE_LIFETIMEBOUND, IViewportResolutionChanger& ResolutionChanger UE_LIFETIMEBOUND, FOverrideShouldHaveOwnership OverrideShouldHaveOwnership = {} );` — @param ViewportLocker Implementation for locking viewports. Outlives the constructed object. @param ResolutionChanger Implementation for changing viewport resolution. Outlives the constructed object. @param OverrideShouldHaveOwnership Optional callback for overriding whether an object should have ownership. Useful for unit tests.
- L48 _public prototype_ `~FViewportManagerBase();`
- L54 _public prototype_ `void RegisterVCamComponent(UVCamComponent& Component);` — Registers Component, so it is now considered for locking the viewport. A viewport will only be locked if one of its output providers has acquired ownership.
- L56 _public prototype_ `void UnregisterVCamComponent(UVCamComponent& Component);` — Component will no longer be considered for viewport locking anymore.
- L59 _public function_ `void RequestLockRefresh()` — Called when something about the lock state has changed and needs refreshing.
- L61 _public function_ `void RequestResolutionRefresh()` — Called when UVCamOutputProviderBase::OverrideResolution, bUseOverrideResolution, or TargetViewport change.
- L66 _private member_ `IViewportLocker& ViewportLocker;` — Talks to engine for changing the lock state of viewports. Used internally by LockManager only.
- L68 _private member_ `IViewportResolutionChanger& ResolutionChanger;` — Talks to engine for changing the resolution of viewports. Used internally by ResolutionManager only.
- L70 _private member_ `const FOverrideShouldHaveOwnership OverrideShouldHaveOwnership;` — Optional callback for overriding whether an object should have ownership. Useful for unit tests
- L79 _private member_ `TOwnershipMapping<EVCamTargetViewportID, TWeakObjectPtr<const UVCamOutputProviderBase>> ViewportOwnership;` — Keeps track what output providers the viewports are owned by. An output provider has ownership over a viewport when: 1. Output provider is outputting 2. Owning UVCamComponent::ViewportLocker is configured to lock OR UVCamOutputProviderBase::NeedsForceLockToViewport.
- L82 _private member_ `FViewportLockManager LockManager;` — Handles logic for locking viewports.
- L84 _private member_ `FViewportResolutionManager ResolutionManager;` — Handles logic for changing viewport resolution.
- L87 _private member_ `TArray<TWeakObjectPtr<UVCamComponent>> RegisteredVCams;` — Components that want to affect the viewport(s).
- L90 _private member_ `bool ViewportShouldPilotStates[4] { false, false, false, false };` — Whether the viewports were set to pilot last tick or not.
- L93 _private member_ `bool bHasRequestedLockRefresh = false;` — Whether locks should be refreshed.
- L95 _private member_ `bool bHasRequestedResolutionRefresh = false;` — Whether viewport resolutions should be refreshed.
- L98 _private prototype_ `void OnEndOfFrame();` — Processes changes made to registered VCams for the purpose updating ownership and then proceeds updating the viewports.
- L101 _private prototype_ `TInlineComponentArray<TWeakObjectPtr<UVCamComponent>> CleanseRegisteredVCams();` — Removes dead registered VCams
- L103 _private prototype_ `void UpdatePilotState(bool bAllowRefresh = true);` — Updates ViewportShouldPilotStates and sets bHasRequestedLockRefresh if it has changed.
- L104 _private function_ `void UpdatePilotStateNoRefresh()`
- L107 _private prototype_ `void UpdateAllOwnership(const TInlineComponentArray<TWeakObjectPtr<UVCamComponent>>& RemovedThisTick);` — Process changes that have occured in this frame and updates ViewportOwnership. Returns whether any changes have been made.
- L109 _private prototype_ `void UpdateOwnershipFor(const FVCamViewportLocker& OwnerLockState, const UVCamOutputProviderBase& OutputProvider);` — Updates ownership for a single OutputProvider.
- L110 _private prototype_ `bool DetermineOwnershipFor(const UVCamOutputProviderBase& OutputProvider, const FVCamViewportLocker& OwnerLockState) const;`
- L113 _private prototype_ `void RemoveOwnership(const UVCamComponent& Component);` — Removes the VCam's output providers from the ownership model.
- L116 _private prototype_ `bool HasViewportOwnership(const UVCamOutputProviderBase& OutputProvider) const;` — Callback passed to LockManager and ResolutionManager for deciding whether a given output provider has ownership over a viewport.

#### class `UE::VCamCore::FViewportManager`  
`class FViewportManager : public FNoncopyable`  
_L123-176_
- inherits: `FNoncopyable`
- desc: Adds look-up functions for special UI constructs (e.g. FSceneViewport, input window, and level editor client) to the manager. Not unit tested.
- L127 _public function_ `FViewportManager() : Implementation(ViewportSystemSwitcher, ViewportSystemSwitcher)`
- L133 _public function_ `void RegisterVCamComponent(UVCamComponent& Component)` — Registers Component, so it is now considered for locking the viewport. A viewport will only be locked if one of its output providers has acquired ownership.
- L135 _public function_ `void UnregisterVCamComponent(UVCamComponent& Component)` — Component will no longer be considered for viewport locking anymore.
- L138 _public function_ `void RequestLockRefresh()` — Called when something about the lock state has changed and needs refreshing.
- L140 _public function_ `void RequestResolutionRefresh()` — Called when UVCamOutputProviderBase::OverrideResolution, bUseOverrideResolution, or TargetViewport change.
- L143 _public function_ `TSharedPtr<FSceneViewport> GetSceneViewport(EVCamTargetViewportID ViewportID) const` — Gets the scene viewport identified by ViewportID.
- L145 _public function_ `TWeakPtr<SWindow> GetInputWindow(EVCamTargetViewportID ViewportID) const` — Gets the window that contains the given viewport.
- L157 _public function_ `FLevelEditorViewportClient* GetEditorViewportClient(EVCamTargetViewportID ViewportID) const` — Gets the FLevelEditorViewportClient that is managing the ViewportID. This will only return valid in the editor environment (thus not work in PIE or games). If the UVCamOutputProviderBase::DisplayType is EVPWidgetDisplayType::PostProcessWithBlendMaterial, the FEditorViewportClient::ViewModifiers are used to overlay the widget into the viewport because it plays nicely with other viewports. In games, the output provider simply places the post process material in the target camera because there is only one viewport. Hence, there is no implementation for games.
- L167 _private member_ `FViewportSystemSwitcher ViewportSystemSwitcher;` — Decides (at compile-time or dynamically) which viewport system should be used for locking. In games, the game viewport can be used. In editors, it depends on whether we're in PIE or not. See the class docu for further info.
- L175 _private member_ `FViewportManagerBase Implementation;` — Composition instead of inheritance so we can fully initialize ViewportSystemSwitcher before passing it down. (Even though it'd be valid C++ passing uninitialized ViewportSystemSwitcher to parent constructor, it's dangerous if somebody in the future changes that constructor to call a function on it.)

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace VCamCore` (scope `UE`)
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<bool>, FOverrideShouldHaveOwnership, const UVCamOutputProviderBase&);` — @return If set, the ownership is overriden with this value. If unset, the default behaviour is used.

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/Viewport/ViewportResolutionManager.h` (Private)


#### class `UE::VCamCore::FViewportResolutionManager`  
`class FViewportResolutionManager : public FNoncopyable`  
_L23-57_
- inherits: `FNoncopyable`
- desc: Takes care of setting the right resolution for every viewport that has an assigned output provider.
- L27 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FHasViewportOwnership, const UVCamOutputProviderBase&);`
- L28 _public prototype_ `FViewportResolutionManager( IViewportResolutionChanger& ResolutionChanger UE_LIFETIMEBOUND, FHasViewportOwnership HasViewportOwnershipDelegate );`
- L34 _public prototype_ `void UpdateViewportLockState(TConstArrayView<TWeakObjectPtr<UVCamComponent>> RegisteredVCams);` — Checks which of the output providers in the given VCam array should lock the viewport.
- L39 _private member_ `IViewportResolutionChanger& ResolutionChanger;` — Talks to the viewport for changing the resolution.
- L42 _private member_ `const FHasViewportOwnership HasViewportOwnershipDelegate;` — Looks up whether the given output provider has ownership over the viewport.
- L51 _private member_ `} ViewportData[4];`
- L53 _private prototype_ `FViewportData& GetViewportData(EVCamTargetViewportID ViewportID);`
- L55 _private prototype_ `void UpdateViewport(TConstArrayView<TWeakObjectPtr<UVCamComponent>> RegisteredVCams, EVCamTargetViewportID ViewportID);`
- L56 _private prototype_ `void UpdateResolutionFor(const UVCamOutputProviderBase& OutputProvider);`

#### struct `UE::VCamCore::FViewportResolutionManager::FViewportData`  
`struct FViewportData`  
_L44-51_
- L46 _public member_ `TWeakObjectPtr<const UVCamOutputProviderBase> CurrentOutputProvider;`
- L48 _public member_ `TOptional<FIntPoint> OverrideResolution;` — Set if we've overriden the resolution.
- L50 _public function_ `bool HasOverriddenResolution() const`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace VCamCore` (scope `UE`)
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FHasViewportOwnership, const UVCamOutputProviderBase&);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/Util/WidgetSnapshotUtils.h` (Private)


#### struct `UE::VCamCore::WidgetSnapshotUtils::FWidgetSnapshotSettings`  
`struct FWidgetSnapshotSettings`  
_L13-19_
- L15 _public member_ `TSet<TSubclassOf<UWidget>> AllowedWidgetClasses;`
- L16 _public member_ `TSet<const FProperty*> AllowedProperties;`
- L18 _public prototype_ `bool IsClassAllowed(TSubclassOf<UWidget> Widget) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace VCamCore` (scope `UE`)
- L11 _namespace_ `namespace WidgetSnapshotUtils` (scope `UE::VCamCore`)
- L22 _prototype_ `FWidgetTreeSnapshot TakeTreeHierarchySnapshot(UUserWidget& Widget, const FWidgetSnapshotSettings& SnapshotSettings = VCamCore::FVCamCoreModule::Get().GetSnapshotSettings());` (scope `UE::VCamCore::WidgetSnapshotUtils`) — Saves the state of the widget
- L24 _prototype_ `bool ApplyTreeHierarchySnapshot(const FWidgetTreeSnapshot& Snapshot, UUserWidget& Widget);` (scope `UE::VCamCore::WidgetSnapshotUtils`) — Applies the data saved in Snapshot to Widget
- L27 _prototype_ `void RetakeSnapshotForWidgetInHierarchy(FWidgetTreeSnapshot& WidgetTreeSnapshot, UWidget& Widget, const FWidgetSnapshotSettings& SnapshotSettings = VCamCore::FVCamCoreModule::Get().GetSnapshotSettings());` (scope `UE::VCamCore::WidgetSnapshotUtils`) — Updates the snapshot only for this widget in the hierarchy if a matching snapshot exists (otherwise does not add it).
- L29 _prototype_ `FWidgetSnapshot TakeWidgetSnapshot(UWidget& Widget, const TSet<const FProperty*>& AllowedProperties);` (scope `UE::VCamCore::WidgetSnapshotUtils`)
- L30 _prototype_ `void ApplyWidgetSnapshot(const FWidgetSnapshot& Snapshot, UWidget& Widget);` (scope `UE::VCamCore::WidgetSnapshotUtils`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/VCamBlueprintAssetUserData.h` (Private)


#### class `UVCamBlueprintAssetUserData`  
`class UVCamBlueprintAssetUserData : public UAssetUserData`  
_L19-27_
- reflection: `UCLASS(Within=VCamComponent, NotEditInlineNew)`
- inherits: `UAssetUserData`
- desc: This asset user data is added if the owning UVCamComponent was created by a Blueprint (simple or complex construction script). UVCamComponent must perform logic when it is transacted (such as undoing placement into level) but CS created components do not have the RF_Transactional flag. This asset user data class exposes a delegate with which the owning UVCamComponent can learn when it was undone. NotEditInlineNew to prevent users from manually creating it in UI.
- L25 _public prototype_ `virtual void PostEditUndo() override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/VCamCore.h` (Private)


#### class `UE::VCamCore::FVCamCoreModule`  
`class FVCamCoreModule : public IVCamCoreModule`  
_L18-62_
- inherits: `IVCamCoreModule`
- L22 _public function_ `static FVCamCoreModule& Get()`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public function_ `virtual const FUnifiedActivationDelegateContainer& OnCanActivateOutputProvider() const override`
- L31 _public function_ `virtual FUnifiedActivationDelegateContainer& OnCanActivateOutputProvider() override`
- L35 _public function_ `FViewportManager& GetViewportManager()` — @return Gets the object that manages locking and adjusting resolution of viewports. Keeps track of viewport ownership.
- L37 _public function_ `FDeferredCleanupHandler& GetDeferredCleanup()` — @return The object responsible for cleaning up rendering resources created by VCams when UWorld is destroyed.
- L39 _public prototype_ `WidgetSnapshotUtils::FWidgetSnapshotSettings GetSnapshotSettings() const;` — @return Gets the settings to use for snapshotting widgets in the VCam HUD.
- L50 _private member_ `FViewportManager ViewportManager;` — Manages interaction with the editor and game viewport system. UVCamComponents and UVCamOutputProviders use this to affect viewports. Ideally we'd pass the required objects to UVCamComponents and UVCamOutputProviders directly but UObjects do not support injection. Hence, we are forced to use the service-locator pattern for accessing the FViewportManager.
- L53 _private member_ `FDeferredCleanupHandler DeferredCleanup;` — Handles cleaning up rendering resources created by VCams when UWorld is destroyed.
- L56 _private member_ `FUnifiedActivationDelegateContainer CanActivateDelegateContainer;` — The delegate container for determining whether an output provider can be activated.
- L59 _private prototype_ `void RegisterSettings();` — Register the module's settings object.
- L61 _private prototype_ `void UnregisterSettings();` — Unregister the module's settings object.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace VCamCore` (scope `UE`)
- L11 _namespace_ `namespace WidgetSnapshotUtils` (scope `UE::VCamCore`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Private/VCamCoreCustomVersion.h` (Private)


#### struct `UE::VCamCore::FVCamCoreCustomVersion`  
`struct FVCamCoreCustomVersion`  
_L9-32_
- L28 _public member_ `const static FGuid GUID;`
- L31 _private prototype_ `FVCamCoreCustomVersion() = delete;`

#### enum `UE::VCamCore::FVCamCoreCustomVersion::Type`  
`enum Type`  
_L11-26_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L21 _public enumerator_ `MoveTargetViewportFromComponentToOutput = 1` — The following properties were changed (for 5.2): - UVCamComponent::TargetViewport was moved to UVCamOutputProviderBase - UVCamComponent::bLockViewportToCamera was reworked to work for multiple viewports in FVCamViewportLocker (now part of UVCamComponent).
- L24 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L25 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/EVCamTargetViewportID.h` (Public)


#### enum `EVCamTargetViewportID`  
`enum class EVCamTargetViewportID : uint8`  
_L15-23_
- reflection: `UENUM(BlueprintType, meta=(DisplayName = "VCam Target Viewport ID"))`
- L17 _public enumerator_ `Viewport1 = 0`
- L18 _public enumerator_ `Viewport2 = 1`
- L19 _public enumerator_ `Viewport3 = 2`
- L20 _public enumerator_ `Viewport4 = 3`
- L22 _public enumerator_ `Count UMETA(Hidden)`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace VCamCore` (scope `UE`)
- L27 _function_ `inline int32 ViewportIdToOrdinality(EVCamTargetViewportID TargetViewport)` (scope `UE::VCamCore`)
- L32 _function_ `inline FString ViewportIdToString(EVCamTargetViewportID TargetViewport)` (scope `UE::VCamCore`)
- L39 _prototype_ `TSharedPtr<SLevelViewport> GetLevelViewport(EVCamTargetViewportID TargetViewport);` (scope `UE::VCamCore`) — Gets the level viewport identified by TargetViewport

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/IVCamCoreModule.h` (Public)


#### class `UE::VCamCore::IVCamCoreModule`  
`class IVCamCoreModule : public IModuleInterface`  
_L12-25_
- inherits: `IModuleInterface`
- L16 _public function_ `static IVCamCoreModule& Get()`
- L22 _public prototype_ `virtual const FUnifiedActivationDelegateContainer& OnCanActivateOutputProvider() const = 0;` — @return Gets the delegate container for determining whether an output provider can be activated.
- L24 _public prototype_ `virtual FUnifiedActivationDelegateContainer& OnCanActivateOutputProvider() = 0;` — @return Gets the delegate container for determining whether an output provider can be activated.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Input/InputVCamSubsystem.h` (Public)


#### class `UInputVCamSubsystem`  
`class UInputVCamSubsystem : public UVCamSubsystem, public IEnhancedInputSubsystemInterface`  
_L27-83_
- reflection: `UCLASS()`
- inherits: `UVCamSubsystem,IEnhancedInputSubsystemInterface`
- desc: Handles all input for UVCamComponent. Essentially maps input devices to UVCamComponents, similar like APlayerController does for gameplay code.
- L33 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L34 _public prototype_ `virtual void Deinitialize() override;`
- L35 _public prototype_ `virtual void InitalizeUserSettings() override;`
- L36 _public function_ `virtual UEnhancedInputUserSettings* GetUserSettings() const override`
- L40 _public prototype_ `virtual void OnUpdate(float DeltaTime) override;`
- L46 _public prototype_ `bool InputKey(const FInputKeyParams& Params);` — `UE_DEPRECATED(5.6, "Use the version of InputKey which takes in a FInputKeyEventArgs instead.")` — Inputs a key on this subsystem's player input which can then be processed as normal during Tick.
- L50 _public prototype_ `bool InputKey(const FInputKeyEventArgs& Params);` — Inputs a key on this subsystem's player input which can then be processed as normal during Tick.
- L53 _public prototype_ `void PushInputComponent(UInputComponent* InInputComponent);` — Pushes this input component onto the stack to be processed by this subsystem's tick function
- L55 _public prototype_ `bool PopInputComponent(UInputComponent* InInputComponent);` — Removes this input component onto the stack to be processed by this subsystem's tick function
- L57 _public prototype_ `const FVCamInputDeviceConfig& GetInputSettings() const;`
- L58 _public prototype_ `void SetInputSettings(const FVCamInputDeviceConfig& Input);`
- L61 _public prototype_ `virtual UEnhancedPlayerInput* GetPlayerInput() const override;`
- L62 _public function_ `virtual TMap<TObjectPtr<const UInputAction>, FInjectedInput>& GetContinuouslyInjectedInputs() override`
- L68 _private member_ `TObjectPtr<UVCamPlayerInput> PlayerInput;` — `UPROPERTY(Transient, Instanced)`
- L70 _private member_ `TSharedPtr<UE::VCamCore::FVCamInputProcessor> InputPreprocessor;`
- L74 _private member_ `TArray<TWeakObjectPtr<UInputComponent>> CurrentInputStack;` — `UPROPERTY(Transient)` — Internal. This is the current stack of InputComponents that is being processed by the PlayerInput.
- L78 _private member_ `TObjectPtr<UEnhancedInputUserSettings> UserSettings;` — `UPROPERTY(Transient)` — The user settings for this subsystem used to store each user's input related settings
- L82 _private member_ `TMap<TObjectPtr<const UInputAction>, FInjectedInput> ContinuouslyInjectedInputs;` — `UPROPERTY(Transient)` — Map of inputs that should be injected every frame. These inputs will be injected when ForcedInput is ticked.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Input/VCamInputDeviceConfig.h` (Public)


#### enum `EVCamInputLoggingMode`  
`enum class EVCamInputLoggingMode : uint8`  
_L8-21_
- reflection: `UENUM()`
- L11 _public enumerator_ `None` — No logging
- L14 _public enumerator_ `OnlyConsumable` — Log only input that are passed down to the input actions (i.e. that passed filtering conditions)
- L17 _public enumerator_ `OnlyGamepad` — Log all gamepad input regardless whether it is passed down to input actions or not (i.e. that passed filtering conditions)
- L20 _public enumerator_ `All` — Log all input, regardless whether it is passed down to input actions or not (i.e. that passed filtering conditions).

#### enum `EVCamInputMode`  
`enum class EVCamInputMode : uint8`  
_L24-49_
- reflection: `UENUM()`
- L30 _public enumerator_ `ConsumeIfUsed` — Input is passed to VCam input actions. Input is consumed if the input action was configured to consume input. Otherwise it is passed down the engine's input stack.
- L38 _public enumerator_ `ConsumeDevice` — Input is passed to VCam input actions. For gamepads, input is always consumed even if no input action used it. For keyboards, input is consumed if it was used by an input action (useful to continue to let the editor receive input).
- L45 _public enumerator_ `DoNotConsume` — Input is passed to VCam input actions. Input is not consumed - even if the input action was configured to consume input. The input is passed down the remainder of the engine's input stack.
- L48 _public enumerator_ `Ignore` — Input is not passed to VCam input actions.

#### struct `FVCamInputDeviceID`  
`struct FVCamInputDeviceID`  
_L52-78_
- reflection: `USTRUCT(BlueprintType)`
- L74 _public member_ `int32 DeviceId = -10;` — `UPROPERTY(EditAnywhere, Category = "Input")` — The ID of an input device. Input device IDs start at 0 and increase by 1 as more devices connect. When a device disconnects, the ID is recycled and becomes available for reassignment to the next device that connects; when a device connects, the lowest possible ID is reassigned. Example: suppose you have three gamepads called A, B, and VCamDevicePairingConfig.h 1. Connect gamepad A > receives ID 0 2. Connect gamepad B > receives ID 1 3. Disconnect gamepad A > gamepad B will still have ID 1 4. Connect the same gamepad A OR another gamepad C > receives ID 0. Note: Keyboards always have ID = 0, mice ID = -1. Note: The first gamepad will have ID = 0 even though keyboards will also have ID 0. Default value of -10 means no input device. There is nothing special about -10 (-1 already used by mice).

#### struct `FVCamInputDeviceConfig`  
`struct FVCamInputDeviceConfig`  
_L82-127_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines the input devices a UVCamComponent will accept input from.
- L92 _public member_ `bool bAllowAllInputDevices = true;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Determines how input devices are filtered: True: Every device is allowed. False: Only input from devices with the IDs in AllowedInputDeviceIds is allowed.
- L111 _public member_ `TArray<FVCamInputDeviceID> AllowedInputDeviceIds;` — `UPROPERTY(EditAnywhere, Category = "Input", meta = (EditCondition = "!bAllowAllInputDevices", EditConditionHides))` — List of input devices from which input can trigger input actions. Typically this is used for gamepads. Input device IDs start at 0 and increase by 1 as more devices connect. When a device disconnects, the ID is recycled and becomes available for reassignment to the next device that connects; when a device connects, the lowest possible ID is reassigned. Example: suppose you have three gamepads called A, B, and VCamDevicePairingConfig.h 1. Connect gamepad A > receives ID 0 2. Connect gamepad B > receives ID 1 3. Disconnect gamepad A > gamepad B will still have ID 1 4. Connect the same gamepad A OR another gamepad C > receives ID 0. Note: Keyboards always have ID = 0, mice ID = -1. Note: The first gamepad will have ID = 0 even though keyboards will also have ID 0.
- L118 _public member_ `EVCamInputMode InputMode = EVCamInputMode::ConsumeIfUsed;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Determines how input is to be treated (is it consumed? is it even allowed?). Note: This applies only to gamepads and keyboards. VCam always ignores mouse input (including mouse buttons).
- L126 _public member_ `EVCamInputLoggingMode LoggingMode = EVCamInputLoggingMode::None;` — `UPROPERTY(EditAnywhere, Category = "Input", AdvancedDisplay)` — What type of input should be logged. Tip: Filter the log by LogVCamInputDebug.

#### Free symbols / members of external scopes

- L76 _function_ `friend bool operator==(const FVCamInputDeviceID& Left, const FVCamInputDeviceID& Right)`
- L77 _function_ `friend bool operator!=(const FVCamInputDeviceID& Left, const FVCamInputDeviceID& Right)`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Input/VCamInputSettings.h` (Public)


#### struct `FVCamInputProfile`  
`struct FVCamInputProfile`  
_L10-19_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `TMap<FName, FKey> MappableKeyOverrides;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")` — Remaps inputs to new keys. This remaps the input action mappings found in the modifiers' InputMappingContext.
- L18 _public prototype_ `bool operator==(const FVCamInputProfile& OtherProfile) const;`

#### class `UVCamInputSettings`  
`class UVCamInputSettings : public UDeveloperSettings`  
_L30-61_
- reflection: `UCLASS(Config=Game, DefaultConfig)`
- inherits: `UDeveloperSettings`
- desc: These settings store input profiles. When a modifier is activated, it registers its UVCamModifier::InputMappingContext (IMC). The mapping context maps enhanced input actions to default keys. An input profile rebinds the default keys to new values. The name of the profile key is the name that was used for the binding in the IMC. You can switch between configured profiles by calling UVCamComponent::SetInputProfileFromName or editing UVCamComponent::InputProfile in the details panel.
- L37 _public member_ `FName DefaultInputProfile;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, BlueprintSetter=SetDefaultInputProfile, Category="Input", meta=(GetOptions=GetInputProfileNames))` — The profile that VCam components should default to.
- L41 _public member_ `TMap<FName, FVCamInputProfile> InputProfiles;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, BlueprintSetter=SetInputProfiles, Category="Input")` — A bunch of profiles that components can switch between
- L45 _public prototype_ `static UVCamInputSettings* GetVCamInputSettings();` — `UFUNCTION(BlueprintCallable, Category="VCam")` — Gets the settings object.
- L49 _public prototype_ `void SetDefaultInputProfile(const FName NewDefaultInputProfile);` — `UFUNCTION(BlueprintCallable, Category="VCam Input")` — Sets DefaultInputProfile and saves it out to the config.
- L52 _public prototype_ `void SetInputProfiles(const TMap<FName, FVCamInputProfile>& NewInputProfiles);` — `UFUNCTION(BlueprintCallable, Category="VCam Input")` — Updates InputProfiles and save it out to the config.
- L56 _public prototype_ `TArray<FName> GetInputProfileNames() const;` — `UFUNCTION(BlueprintCallable, Category="VCam Input")` — @return All configured profiles
- L59 _public prototype_ `virtual void PostInitProperties() override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Input/VCamPlayerInput.h` (Public)


#### class `UVCamPlayerInput`  
`class UVCamPlayerInput : public UEnhancedPlayerInput`  
_L14-31_
- reflection: `UCLASS()`
- inherits: `UEnhancedPlayerInput`
- desc: Receives raw input from input processor (or player controller in user code). Filters input
- L20 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& Params) override;`
- L23 _public function_ `const FVCamInputDeviceConfig& GetInputSettings() const`
- L24 _public prototype_ `void SetInputSettings(const FVCamInputDeviceConfig& Input);`
- L30 _private member_ `FVCamInputDeviceConfig InputDeviceSettings;` — `UPROPERTY(Transient)` — The device settings governing what we do with received input, e.g. filtering depending on input device, logging, etc.

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Interface/IVCamOutputProviderCreatedWidget.h` (Public)


#### struct `FVCamReceiveOutputProviderData`  
`struct FVCamReceiveOutputProviderData`  
_L12-18_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `TObjectPtr<UVCamOutputProviderBase> OutputProvider;` — `UPROPERTY(BlueprintReadOnly, Category = "Virtual Camera")`

#### class `UVCamOutputProviderCreatedWidget`  
`class UVCamOutputProviderCreatedWidget : public UInterface`  
_L21-24_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UInterface`

#### class `IVCamOutputProviderCreatedWidget`  
`class IVCamOutputProviderCreatedWidget`  
_L30-38_
- desc: Implemented by widgets that are either directly or indirectly created via an output provider's UMGClass. Receives important events, such as when a widget has been created by an output provider.
- L37 _public prototype_ `void ReceiveOutputProvider(const FVCamReceiveOutputProviderData& Data);` — `UFUNCTION(BlueprintNativeEvent, Category = "Virtual Camera")` — This is called to let widgets know of the output provider that created them.

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Modifier/ModifierStackEntry.h` (Public)


#### struct `FModifierStackEntry`  
`struct FModifierStackEntry`  
_L12-73_
- reflection: `USTRUCT()`
- desc: Links a Modifier with a Name for use in a Modifier Stack
- L18 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, Category="Modifier")` — Identifier for this modifier in the stack
- L22 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category="Modifier")` — Controls whether the modifier actually gets applied
- L26 _public member_ `TObjectPtr<UVCamModifier> GeneratedModifier = nullptr;` — `UPROPERTY(EditAnywhere, Instanced, Category="Modifier")` — The current generated modifier instance
- L30 _public member_ `FGuid EditorGuid;` — GUID used in the editor to identify specific stack entries during editor operations
- L33 _public function_ `FModifierStackEntry()`
- L40 _public function_ `FModifierStackEntry(UVCamModifier& Modifier) : GeneratedModifier(&Modifier)`
- L45 _public function_ `FModifierStackEntry(const FName& InName, const TSubclassOf<UVCamModifier> InModifierClass, UObject* InOuter) : Name(InName)` — If ModifierClass is provided then you must also supply a valid outer for the generated modifier
- L58 _public function_ `bool operator==(const FModifierStackEntry& Other) const`
- L69 _public function_ `bool operator!=(const FModifierStackEntry& Other) const`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Modifier/VCamModifier.h` (Public)


#### struct `FVCamModifierConnectionPoint`  
`struct FVCamModifierConnectionPoint`  
_L18-25_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `TObjectPtr<UInputAction> AssociatedAction;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")` — An optional action to associate with this connection point.

#### class `UVCamModifier`  
`class UVCamModifier : public UObject`  
_L28-82_
- reflection: `UCLASS(Abstract, Blueprintable, EditInlineNew)`
- inherits: `UObject`
- L33 _public prototype_ `virtual void Initialize(UVCamModifierContext* Context, UInputComponent* InputComponent = nullptr);`
- L34 _public prototype_ `virtual void Deinitialize();`
- L37 _public function_ `virtual void Apply(UVCamModifierContext* Context, UCineCameraComponent* CameraComponent, const float DeltaTime)` — Called every tick to update this modifier.
- L40 _public prototype_ `virtual void BeginDestroy() override;`
- L41 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L44 _public function_ `bool IsInitialized() const`
- L47 _public prototype_ `UVCamComponent* GetOwningVCamComponent() const;` — `UFUNCTION(BlueprintCallable, Category="VirtualCamera")`
- L50 _public prototype_ `void GetCurrentLiveLinkDataFromOwningComponent(FLiveLinkCameraBlueprintData& LiveLinkData);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L53 _public prototype_ `void SetEnabled(bool bNewEnabled);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L55 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", meta=(ReturnDisplayName="Enabled"))`
- L60 _public prototype_ `bool SetStackEntryName(FName NewName);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", meta=(ReturnDisplayName="Success"))` — Sets the name of the modifier in the associated modifier stack Returns a bool for whether
- L63 _public prototype_ `FName GetStackEntryName() const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", meta=(ReturnDisplayName="Name"))` — Gets the name of the modifier in the associated modifier stack
- L67 _public member_ `TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="VCam Input", meta=(EditCondition="bRegisterForInput"))` — If an Input Mapping Context is specified then that Context will be automatically added to the input system when this Modifier is Initialized
- L71 _public member_ `int32 InputContextPriority = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="VCam Input", meta=(EditCondition="bRegisterForInput"))` — If an Input Mapping Context is provided then this value defines the priority level that the context is added to the input system with
- L74 _public member_ `TMap<FName, FVCamModifierConnectionPoint> ConnectionPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VCam Connection Points")`
- L78 _private prototype_ `FModifierStackEntry* GetCorrespondingStackEntry() const;`
- L81 _private member_ `bool bNeedsInitialization = true;` — `UPROPERTY(Transient)`

#### class `UVCamBlueprintModifier`  
`class UVCamBlueprintModifier : public UVCamModifier`  
_L85-108_
- reflection: `UCLASS(Abstract, EditInlineNew)`
- inherits: `UVCamModifier`
- L90 _public prototype_ `virtual void Initialize(UVCamModifierContext* Context, UInputComponent* InputComponent=nullptr) override;`
- L91 _public prototype_ `virtual void Deinitialize() override;`
- L92 _public prototype_ `virtual void Apply(UVCamModifierContext* Context, UCineCameraComponent* CameraComponent, const float DeltaTime) override;`
- L95 _public prototype_ `void OnInitialize(UVCamModifierContext* Context);` — `UFUNCTION(BlueprintImplementableEvent, Category="VirtualCamera")`
- L98 _public prototype_ `void OnDeinitialize();` — `UFUNCTION(BlueprintImplementableEvent, Category="VirtualCamera")`
- L102 _public prototype_ `void OnApply(UVCamModifierContext* Context, UCineCameraComponent* CameraComponent, const float DeltaTime);` — `UFUNCTION(BlueprintImplementableEvent, Category="VirtualCamera")` — Called every tick to update this modifier.
- L107 _public prototype_ `void GetInputMappingContextAndPriority() const;` — `UFUNCTION(BlueprintImplementableEvent, Category="VirtualCamera")` — This function is deliberately non-working to force cleanup of Input Contexts Please move any previous values to the new properties in Class Defaults

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Modifier/VCamModifierContext.h` (Public)


#### class `UVCamModifierContext`  
`class UVCamModifierContext : public UObject`  
_L9-12_
- reflection: `UCLASS(Blueprintable, Abstract, EditInlineNew)`
- inherits: `UObject`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Output/Data/EViewportChangeReply.h` (Public)


#### enum `UE::VCamCore::EViewportChangeReply`  
`enum class EViewportChangeReply : uint8`  
_L10-20_
- desc: Result of UVCamOutputProviderBase::PreReapplyViewport
- L17 _public enumerator_ `Reinitialize` — Returned by PreReapplyViewport that the subclass wants the entire output provider to be reinitialized. This could be returned e.g. because changing the viewport while outputting is not supported by this implementation. Do not call PostReapplyViewport after reinitialization is performed.
- L19 _public enumerator_ `ApplyViewportChange` — The viewport change will be processed by the implementation. Continue reapplying the output widget to the new target viewport and then call PostReapplyViewport.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Output/Data/VCamStringPrompt.h` (Public)


#### enum `EVCamStringPromptResult`  
`enum class EVCamStringPromptResult : uint8`  
_L12-25_
- reflection: `UENUM(BlueprintType)`
- desc: Result of a request for string input from a VCam streaming client
- L15 _public enumerator_ `Submitted` — The user submitted a string, which is contained in the response's Input field
- L18 _public enumerator_ `Cancelled` — The user cancelled the string prompt
- L21 _public enumerator_ `Disconnected` — The user disconnected before responding to the string prompt
- L24 _public enumerator_ `Unavailable` — String prompts are not available in the current VCam configuration

#### struct `FVCamStringPromptResponse`  
`struct FVCamStringPromptResponse`  
_L29-46_
- reflection: `USTRUCT(BlueprintType)`
- desc: Response to a request for string input from a VCam streaming client
- L33 _public function_ `FVCamStringPromptResponse()`
- L35 _public function_ `FVCamStringPromptResponse(EVCamStringPromptResult Result, FString Entry = "") : Result(Result), Entry(Entry)`
- L41 _public member_ `EVCamStringPromptResult Result = EVCamStringPromptResult::Unavailable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VCam)` — The result of the string prompt
- L45 _public member_ `FString Entry = "";` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VCam)` — The string that the user provided. Empty if the result is not Submitted.

#### struct `FVCamStringPromptRequest`  
`struct FVCamStringPromptRequest`  
_L50-59_
- reflection: `USTRUCT(BlueprintType)`
- desc: Request for string input which will be sent to a VCam streaming client
- L55 _public member_ `FString DefaultValue;` — The default value to show in the client's text input form
- L58 _public member_ `FString PromptTitle;` — The title to show in the client's text input form

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Output/VCamOutputComposure.h` (Public)


#### class `UVCamOutputComposure`  
`class UE_DEPRECATED(5.7, "Composure output provider has been deprecated and will be removed.") UVCamOutputComposure : public UVCamOutputProviderBase`  
_L13-31_
- reflection: `UCLASS()`
- inherits: `UVCamOutputProviderBase`
- L20 _public member_ `TArray<TSoftObjectPtr<AActor>> LayerTargets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")` — List of Composure stack Compositing Elements to render the requested UMG into
- L25 _public member_ `TObjectPtr<UTextureRenderTarget2D> FinalOutputRenderTarget_DEPRECATED = nullptr;` — `UE_DEPRECATED(5.7, "UVCamOutputProviderBase now provides a final output render target.")` — `UPROPERTY()` — TextureRenderTarget2D asset that contains the final output
- L27 _public prototype_ `UVCamOutputComposure();`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Output/VCamOutputMediaOutput.h` (Public)


#### class `UVCamOutputMediaOutput`  
`class UVCamOutputMediaOutput: public UVCamOutputProviderBase`  
_L15-48_
- reflection: `UCLASS(meta = (DisplayName = "Media Output Provider"))`
- inherits: `UVCamOutputProviderBase`
- L22 _public member_ `TObjectPtr<UMediaOutput> OutputConfig;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")` — Media Output configuration asset
- L26 _public member_ `int32 FromComposureOutputProviderIndex_DEPRECATED = INDEX_NONE;` — `UE_DEPRECATED(5.7, "Using composure as an output provider is no longer supported. You can specify a final render target directly on the output provider.")` — `UPROPERTY()`
- L28 _public prototype_ `UVCamOutputMediaOutput();`
- L31 _public prototype_ `virtual void OnActivate() override;`
- L32 _public prototype_ `virtual void OnDeactivate() override;`
- L36 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _protected member_ `TObjectPtr<UMediaCapture> MediaCapture = nullptr;` — `UPROPERTY(Transient)`
- L46 _private prototype_ `void StartCapturing();`
- L47 _private prototype_ `void StopCapturing();`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Output/VCamOutputProviderBase.h` (Public)


#### class `UVCamOutputProviderBase`  
`class UVCamOutputProviderBase : public UObject`  
_L49-341_
- reflection: `UCLASS(Abstract, BlueprintType, EditInlineNew, CollapseCategories)`
- inherits: `UObject`
- desc: Output providers implement methods of overlaying a widget onto a target viewport. The composition of viewport and widget is then usually streamed to an application outside the engine, e.g. via Pixel Streaming or Remote Session. To start outputting, the owning UVCamComponent must be enabled and the output provider activated. Output providers are managed by UVCamComponent, which own them and must be attached as a child to a UCineCameraComponent. Output providers have a target viewport that the widget is overlayed onto. The target viewport can be locked to the target camera, which happens when: 1. The output provider is outputting IsOutputting() == true 2. The output provider is configured to do so, either by 2.1 NeedsForceLockToViewport returning true or 2.2 UVCamComponent::ViewportLocker being configured accordingly. When a viewport is locked, the owning output provider can affect its resolution (see bUseOverrideResolution and OverrideResolution). A concept of viewport ownership is implemented in FViewportManager ensuring that at most 1 output provider affects a viewport's lock and resolution at a time; the first output provider to request lock, gets the ownership over that viewport. When lock, resolution or target viewport change, call RequestResolutionRefresh to updat the viewport state.
- L55 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FActivationDelegate, bool );`
- L56 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivationDelegate_Blueprint, bool, bNewIsActive);`
- L57 _public member_ `FActivationDelegate OnActivatedDelegate;`
- L60 _public member_ `FActivationDelegate_Blueprint OnActivatedDelegate_Blueprint;` — `UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnActivated"))` — Called when the activation state of this output provider changes.
- L64 _public member_ `bool bUseOverrideResolution = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (DisplayPriority = "5"))` — Override the default output resolution with a custom value - NOTE you must toggle bIsActive off then back on for this to take effect
- L68 _public member_ `FIntPoint OverrideResolution = { 2048, 1536 };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (DisplayPriority = "6"), meta = (EditCondition = "bUseOverrideResolution", ClampMin = 1))` — When bUseOverrideResolution is set, use this custom resolution
- L70 _public prototype_ `UVCamOutputProviderBase();`
- L73 _public prototype_ `virtual void BeginDestroy() override;`
- L80 _public prototype_ `virtual void Initialize();` — Called when the provider is brought online such as after instantiating or loading a component containing this provider Use Initialize for any setup logic that needs to survive between Start / Stop cycles such as spawning transient objects
- L82 _public prototype_ `virtual void Deinitialize();` — Called when the provider is being shutdown such as before changing level or on exit
- L84 _public prototype_ `virtual void Tick(const float DeltaTime);`
- L87 _public prototype_ `virtual bool NeedsForceLockToViewport() const;` — @return Whether this output provider should require the viewport to be locked to the camera in order to function correctly.
- L93 _public function_ `virtual TFuture<FVCamStringPromptResponse> PromptClientForString(const FVCamStringPromptRequest& Request)` — Request string input from the streaming client. Returns true if the request was handled.
- L99 _public prototype_ `void SuspendOutput();` — Temporarily disable the output.  Caller must eventually call RestoreOutput.
- L101 _public prototype_ `void RestoreOutput();` — Restore the output state from previous call to disable output.
- L104 _public prototype_ `void NotifyAboutComponentChange();` — Calls the VCamModifierInterface on the widget if it exists and also requests any child VCam Widgets to reconnect
- L108 _public prototype_ `void SetActive(const bool bInActive);` — `UFUNCTION(BlueprintCallable, Category = "Output")` — Called to turn on or off this output provider
- L111 _public function_ `bool IsActive() const` — `UFUNCTION(BlueprintPure, Category = "Output")` — Returns if this output provider is currently active or not
- L115 _public function_ `bool IsInitialized() const` — `UFUNCTION(BlueprintPure, Category = "Output")` — Returns if this output provider has been initialized or not
- L118 _public function_ `EVCamTargetViewportID GetTargetViewport() const` — `UFUNCTION(BlueprintPure, Category = "Output")`
- L120 _public prototype_ `void SetTargetViewport(EVCamTargetViewportID Value);` — `UFUNCTION(BlueprintCallable, Category = "Output")`
- L122 _public prototype_ `void InitTargetViewport(EVCamTargetViewportID Value);` — Uses this version in constructors (e.g. for initializing a CDO).
- L125 _public function_ `TSubclassOf<UUserWidget> GetUMGClass() const` — `UFUNCTION(BlueprintPure, Category = "Output")`
- L127 _public prototype_ `void SetUMGClass(const TSubclassOf<UUserWidget> InUMGClass);` — `UFUNCTION(BlueprintCallable, Category = "Output")`
- L130 _public prototype_ `UVCamComponent* GetVCamComponent() const;` — `UFUNCTION(BlueprintPure, Category = "Output")`
- L131 _public function_ `UViewportWidgetOverlay* GetUMGWidget()`
- L134 _public function_ `UVCamOutputProviderBase* GetOtherOutputProviderByIndex(int32 Index) const` — Utility that gets the owning VCam component and gets another output provider by its index.
- L136 _public function_ `int32 FindOwnIndexInOwner() const` — Gets the index of this output provider in the owning UVCamComponent::OutputProviders array.
- L139 _public function_ `void ReapplyOverrideResolution() const` — `UE_DEPRECATED(5.5, "Use RequestResolutionRefresh instead")`
- L146 _public prototype_ `void RequestResolutionRefresh() const;` — Requests that at end of the frame the target viewport's resolution is updated to match this provider's settings. The update will have no effect if this output provider does not have ownership over the target viewport; ownership is granted if the viewport is locked to this output provider (either NeedsForceLockToViewport returns true or the UVCamComponent::ViewportLocker is configured accordingly).
- L149 _public function_ `TSharedPtr<FSceneViewport> GetTargetSceneViewport() const` — Gets the scene viewport identified by the currently configured TargetViewport.
- L151 _public prototype_ `TSharedPtr<FSceneViewport> GetSceneViewport(EVCamTargetViewportID InTargetViewport) const;` — Gets the viewport identified by the passed in parameters.
- L152 _public prototype_ `TWeakPtr<SWindow> GetTargetInputWindow() const;`
- L155 _public prototype_ `bool IsActivationChangeAllowed(bool bRequestActiveState);` — @return Whether it is allowed to change the activation state into bRequestActiveState.
- L157 _public prototype_ `bool IsActivationChangeAllowedWithReason(bool bRequestActiveState, FText& OutReason);` — @return Whether it is allowed to change the activation state into bRequestActiveState. OutReason is only set if the return value is false.
- L160 _public function_ `bool CanToggleActivation()` — `UFUNCTION(BlueprintPure, Category = "Output")` — @return Whether it is allowed to toggle (true -> false, false -> true) the activation state of this output provider.
- L163 _public function_ `bool IsOutputting() const` — @return Whether this output provider is currently outputting (initialized, active, and owning VCam is enabled).
- L164 _public function_ `UGameplayViewTargetPolicy* GetGameplayViewTargetPolicy() const`
- L167 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L168 _public prototype_ `virtual void PostLoad() override;`
- L173 _public prototype_ `virtual void PreEditUndo() override;`
- L174 _public prototype_ `virtual void PostEditUndo() override;`
- L175 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L179 _public function_ `static FName GetIsActivePropertyName()`
- L180 _public function_ `static FName GetTargetViewportPropertyName()`
- L181 _public function_ `static FName GetUMGClassPropertyName()`
- L185 _public function_ `UTextureRenderTarget2D* GetFinalOutputRenderTarget() const` — `UFUNCTION(BlueprintGetter)` — Get the current TexturRenderTarget2D for the output provider. This value can be null.
- L192 _public function_ `void SetFinalOutputRenderTarget(UTextureRenderTarget2D* InFinalOuputRenderTarget)` — `UFUNCTION(BlueprintSetter)` — Set the current TexturRenderTarget2D for the output provider. Null values are allowed.
- L206 _protected member_ `TObjectPtr<UTextureRenderTarget2D> FinalOutputRenderTarget = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintGetter=GetFinalOutputRenderTarget, BlueprintSetter=SetFinalOutputRenderTarget, Category = "Output")` — TextureRenderTarget2D asset that contains the final output. If specified, this render target will be output by the provider. This allows you to do custom compositing before outputting happens. The details depend on the output provider subclass implementation. For example, the pixel streaming output provider outputs the viewport by default. If FinalOutputRenderTarget is specified, the specified render target is streamed instead of the viewport.
- L210 _protected member_ `EViewportWidgetOverlay_DisplayType DisplayType = EViewportWidgetOverlay_DisplayType::Inactive;` — `UPROPERTY(Transient)` — Defines how the overlay widget should be added to the viewport. This should set as early as possible: in the constructor.
- L220 _protected member_ `TObjectPtr<UGameplayViewTargetPolicy> GameplayViewTargetPolicy;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Output", meta = (DisplayPriority = "99"))` — In game worlds, such as PIE or shipped games, determines which a player controller whose view target should be set to the owning cine camera. Note that multiple output providers may have a policy set and policies might choose the same player controllers to set the view target for. This conflict is resolved as follows: if a player controller already has the cine camera as view target, the policy is not used. Hence, you can order your output providers array in the VCamComponent. The first policies will get automatically get higher priority.
- L223 _protected prototype_ `void SetActiveInternal(bool bInActive);` — Triggers all callbacks without checking whether the bIsActive flag is actually being changed.
- L226 _protected prototype_ `virtual void OnActivate();` — Called when the provider is Activated
- L228 _protected prototype_ `virtual void OnDeactivate();` — Called when the provider is Deactivated
- L231 _protected prototype_ `virtual void CreateUMG();` — Called to create the UMG overlay widget.
- L232 _protected prototype_ `void DisplayUMG();`
- L233 _protected prototype_ `void DestroyUMG();`
- L235 _protected prototype_ `void DisplayNotification_ViewportNotFound() const;`
- L238 _protected prototype_ `void OnSetTargetCamera(const UCineCameraComponent* InTargetCamera);` — Called by owning UVCamComponent when the target camera changes.
- L241 _protected prototype_ `FLevelEditorViewportClient* GetTargetLevelViewportClient() const;`
- L250 _protected prototype_ `void ReinitializeViewportIfNeeded();` — Called after changing viewport. Handles processing all updates that must happen in response: 1. Updating the override viewport resolutions 2. Warning user that the target viewport is not available (they should open the viewport x tab) 3. If currently outputting, recreate the UMG widget into the new target viewport.
- L252 _protected prototype_ `void ReinitializeViewport();` — Called while a UMG widget is being outputted. This moves the displayed UMG widget from the old viewport to the new target viewport.
- L258 _protected function_ `virtual UE::VCamCore::EViewportChangeReply PreReapplyViewport()` — Called a new target viewport has been set while outputting but before the viewport change is processed. Subclass can indicate whether the dynamic change is supported or not.
- L260 _protected function_ `virtual void PostReapplyViewport()` — If PreReapplyViewport returned EVCamViewportChangeReply::ApplyViewportChange, then this function is called after the UMG widget has been placed in the new target viewport.
- L262 _protected function_ `UViewportWidgetOverlay* GetUMGWidget() const`
- L268 _private member_ `bool bIsActive = false;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "IsActive", BlueprintSetter = "SetActive", Category = "Output", meta = (EditCondition = "CanToggleActivation", DisplayPriority = "1"))` — If set, this output provider will execute every frame
- L278 _private member_ `bool bIsActuallyActive = false;` — `UPROPERTY(Transient, NonTransactional)` — This makes sure that every OnActivate call is matched with exactly one OnDeactivate call, and vice versa. These functions allocate external resources (e.g. signalling server in pixel streaming), so the calls must be matched exactly. Without this variable, it would be difficult to keep track of whether we're actually active because of the many systems that set  bIsActive directly, e.g. undo / redo and Multi-User.
- L282 _private member_ `EVCamTargetViewportID TargetViewport = EVCamTargetViewportID::Viewport1;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetTargetViewport", BlueprintSetter = "SetTargetViewport", Category = "Output", meta = (DisplayPriority = "2"))` — Which viewport to use for this VCam
- L286 _private member_ `TSubclassOf<UUserWidget> UMGClass;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetUMGClass", BlueprintSetter = "SetUMGClass", Category = "Output", meta = (DisplayName="UMG Overlay", DisplayPriority = "3"))` — The UMG class to be rendered in this output provider
- L290 _private member_ `FWidgetTreeSnapshot WidgetSnapshot;` — `UPROPERTY()` — FOutputProviderLayoutCustomization allows remapping connections and their bound widgets. This is used to persist those overrides since UUserWidgets cannot be saved.
- L293 _private member_ `bool bInitialized = false;` — `UPROPERTY(Transient, NonTransactional)`
- L297 _private member_ `TObjectPtr<UViewportWidgetOverlay> UMGWidget = nullptr;` — `UPROPERTY(Transient, NonTransactional)` — Valid when active and if UMGClass is valid.
- L302 _private member_ `FPostProcessSettings PostProcessSettingsForWidget;` — `UPROPERTY(Transient)` — We call UVPFullScreenUserWidget::SetCustomPostProcessSettingsSource(this), which will cause these settings to be discovered. They are later passed down to FEditorViewportViewModifierDelegate.
- L306 _private member_ `bool bIsUndoing = false;` — `UPROPERTY(Transient, NonTransactional)` — Prevents certain messages from being generated while undoing.
- L309 _private member_ `FDelegateHandle ModifyViewportPostProcessSettingsDelegateHandle;` — Handle to ModifyViewportPostProcessSettings
- L313 _private member_ `TSoftObjectPtr<UCineCameraComponent> TargetCamera;` — `UPROPERTY(Transient)`
- L317 _private member_ `bool bWasOutputSuspendedWhileActive = false;` — `UPROPERTY(Transient)` — SuspendOutput can disable output while we're active. This flag indicates whether we should reactivate when RestoreOutput is called.
- L321 _private member_ `TSet<TWeakObjectPtr<APlayerController>> PlayersWhoseViewTargetsWereSet;` — `UPROPERTY(Transient, NonTransactional)` — If in a game world, these player controllers must have their view targets reverted when this output provider is deactivated.
- L323 _private function_ `bool IsActiveAndOuterComponentAllowsActivity(bool bSkipGarbageCheck = false) const`
- L324 _private prototype_ `bool IsOuterComponentEnabledAndInitialized(bool bSkipGarbageCheck = false) const;`
- L327 _private prototype_ `void HandleCallingOnActivate();` — Calls OnActivate, it it has not yet been.
- L329 _private prototype_ `void HandleCallingOnDeactivate();` — Calls OnDeactivate, it it has not yet been.
- L333 _private prototype_ `void ModifyViewportPostProcessSettings(FEditorViewportViewModifierParams& EditorViewportViewModifierParams);` — Passed to FEditorViewportClient::ViewModifiers whenever DisplayType == EVPWidgetDisplayType::PostProcessWithBlendMaterial.
- L335 _private prototype_ `TOptional<bool> GetRenderWidgetStateInContext(const ISceneViewExtension* SceneViewExtension, const FSceneViewExtensionContext& Context);` — Callback when DisplayType == EVPWidgetDisplayType::PostProcessSceneViewExtension that decides whether a given viewport should be rendered to.
- L337 _private prototype_ `void StartDetectAndSnapshotWhenConnectionsChange();`
- L338 _private prototype_ `void StopDetectAndSnapshotWhenConnectionsChange();`
- L339 _private prototype_ `void OnConnectionReinitialized(TWeakObjectPtr<UVCamWidget> Widget);`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamOutputProvider, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamOutputProvider, Log, All);`
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FActivationDelegate, bool );`
- L56 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivationDelegate_Blueprint, bool, bNewIsActive);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Output/VCamOutputRemoteSession.h` (Public)


#### class `UVCamOutputRemoteSession`  
`class UVCamOutputRemoteSession : public UVCamOutputProviderBase`  
_L12-64_
- reflection: `UCLASS(meta = (DisplayName = "Unreal Remote Output Provider"))`
- inherits: `UVCamOutputProviderBase`
- L19 _public member_ `int32 PortNumber = IRemoteSessionModule::kDefaultPort;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")` — Network port number - change this only if connecting multiple RemoteSession devices to the same PC
- L23 _public member_ `int32 FromComposureOutputProviderIndex_DEPRECATED = INDEX_NONE;` — `UE_DEPRECATED(5.7, "Using composure as an output provider is no longer supported. You can specify a final render target directly on the output provider.")` — `UPROPERTY()`
- L25 _public prototype_ `UVCamOutputRemoteSession();`
- L28 _public prototype_ `virtual void Initialize() override;`
- L29 _public prototype_ `virtual void Deinitialize() override;`
- L30 _public prototype_ `virtual void OnActivate() override;`
- L31 _public prototype_ `virtual void OnDeactivate() override;`
- L32 _public prototype_ `virtual void Tick(const float DeltaTime) override;`
- L37 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L44 _protected member_ `TObjectPtr<URemoteSessionMediaOutput> MediaOutput = nullptr;` — `UPROPERTY(Transient)`
- L47 _protected member_ `TObjectPtr<URemoteSessionMediaCapture> MediaCapture = nullptr;` — `UPROPERTY(Transient)`
- L51 _private member_ `TSharedPtr<IRemoteSessionUnmanagedRole> RemoteSessionHost;`
- L52 _private member_ `FHitResult LastViewportTouchResult;`
- L53 _private member_ `bool bUsingDummyUMG = false;`
- L55 _private prototype_ `void CreateRemoteSession();`
- L56 _private prototype_ `void DestroyRemoteSession();`
- L58 _private prototype_ `void OnRemoteSessionChannelChange(IRemoteSessionRole* Role, TWeakPtr<IRemoteSessionChannel> Channel, ERemoteSessionChannelChange Change);`
- L59 _private prototype_ `void OnImageChannelCreated(TWeakPtr<IRemoteSessionChannel> Instance);`
- L60 _private prototype_ `void OnInputChannelCreated(TWeakPtr<IRemoteSessionChannel> Instance);`
- L61 _private prototype_ `void OnTouchEventOutsideUMG(const FVector2D& InViewportPosition);`
- L63 _private prototype_ `bool DeprojectScreenToWorld(const FVector2D& InScreenPosition, FVector& OutWorldPosition, FVector& OutWorldDirection) const;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Output/VCamOutputViewport.h` (Public)


#### class `UVCamOutputViewport`  
`class UVCamOutputViewport : public UVCamOutputProviderBase`  
_L10-16_
- reflection: `UCLASS(meta = (DisplayName = "Viewport Output Provider"))`
- inherits: `UVCamOutputProviderBase`
- desc: Adds a widget on top of the viewport locally.
- L15 _public prototype_ `UVCamOutputViewport();`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Output/ViewTargetPolicy/FocusFirstPlayerViewTargetPolicy.h` (Public)


#### class `UFocusFirstPlayerViewTargetPolicy`  
`class UFocusFirstPlayerViewTargetPolicy : public UGameplayViewTargetPolicy`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UGameplayViewTargetPolicy`
- desc: Chooses the first local player controller.
- L18 _public prototype_ `virtual TArray<APlayerController*> DeterminePlayerControllers_Implementation(const FDeterminePlayerControllersTargetPolicyParams& Params) override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Output/ViewTargetPolicy/GameplayViewTargetPolicy.h` (Public)


#### struct `FDeterminePlayerControllersTargetPolicyParams`  
`struct FDeterminePlayerControllersTargetPolicyParams`  
_L13-28_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `TObjectPtr<UVCamOutputProviderBase> OutputProvider;` — `UPROPERTY(BlueprintReadWrite, Category = "VirtualCamera")` — The output provider in question
- L23 _public member_ `TObjectPtr<UCineCameraComponent> CameraToAffect;` — `UPROPERTY(BlueprintReadWrite, Category = "VirtualCamera")` — The camera the output provider is associated with.
- L27 _public member_ `bool bNewIsActive {};` — `UPROPERTY(BlueprintReadWrite, Category = "VirtualCamera")` — Whether the output provider will be made active or inactive.

#### struct `FUpdateViewTargetPolicyParams`  
`struct FUpdateViewTargetPolicyParams : public FDeterminePlayerControllersTargetPolicyParams`  
_L31-38_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDeterminePlayerControllersTargetPolicyParams`
- L37 _public member_ `TArray<TObjectPtr<APlayerController>> PlayerControllers;` — `UPROPERTY(BlueprintReadWrite, Category = "VirtualCamera")` — The player controllers whose view targets should be set to CameraToAffect.

#### class `UGameplayViewTargetPolicy`  
`class UGameplayViewTargetPolicy : public UObject`  
_L47-67_
- reflection: `UCLASS(Abstract, Blueprintable, EditInlineNew)`
- inherits: `UObject`
- desc: A gameplay view target policy determines which player controller should change its view target when gameplay is started, e.g. PIE or in shipped games. Some output providers, such as pixel streaming, require the view target to be set to the cine camera
- L57 _public prototype_ `TArray<APlayerController*> DeterminePlayerControllers(const FDeterminePlayerControllersTargetPolicyParams& Params);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "VirtualCamera")` — Called when the policy should be applied: when the output provider's activation changes in a game world. @return The player controllers for which the view target should be set to the output provider's camera. Typically contains 1 element but you can return more if you wish.
- L66 _public prototype_ `void UpdateViewTarget(const FUpdateViewTargetPolicyParams& Params);` — `UFUNCTION(BlueprintNativeEvent, Category = "VirtualCamera")` — Called to just after the view target has been updated for the player controller that was previously returned by DeterminePlayerController. The default implementation sets the view target without a blend. You can override this to do a blend or perform additional actions. Note this is also called when the the owning output provider is deactivated (so you can possibly reset the view target to be the old player controller's pawn).

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/UI/Switcher/VCamStateSwitcherWidget.h` (Public)


#### class `UVCamStateSwitcherWidget`  
`class UVCamStateSwitcherWidget : public UVCamWidget`  
_L19-82_
- reflection: `UCLASS()`
- inherits: `UVCamWidget`
- desc: A widget that has a set of states you can switch between using SetCurrentState. A state is a collection of VCamWidgets whose connections should be rebound to new connection points.
- L22 _private member_ `static FName DefaultState;`
- L26 _public function_ `void K2_SetCurrentState(FName NewState)` — `UFUNCTION(BlueprintCallable, Category = "Connections", meta = (BlueprintInternalUseOnly = "true"))`
- L37 _public prototype_ `bool SetCurrentState(FName NewState, bool bForceUpdate = false, bool bReinitializeConnections = true);` — `UFUNCTION(BlueprintCallable, Category = "Connections")` — Switches to given state - if the state transition is valid, UpdateConnectionTargets will be called. If CurrentState == NewState, then this call will be ignored (unless bForceUpdate == true). @param NewState The new state to switch to @param bForceUpdate Call UpdateConnectionTargets even if the CurrentState == NewState @param bReinitializeConnections Parameter to pass to UpdateConnectionTargets. If true, ReinitializeConnections will be called.
- L40 _public function_ `FName GetCurrentState() const` — `UFUNCTION(BlueprintPure, Category = "Connections")`
- L43 _public prototype_ `TArray<FName> GetStates() const;` — `UFUNCTION(BlueprintPure, Category = "Connections")`
- L46 _public prototype_ `bool GetStateInfo(FName State, FVCamWidgetConnectionState& OutStateInfo) const;` — `UFUNCTION(BlueprintPure, Category = "Connections")`
- L49 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L52 _public function_ `FORCEINLINE static FName GetCurrentStatePropertyName()`
- L57 _protected prototype_ `virtual void NativePreConstruct() override;`
- L61 _protected prototype_ `virtual void OnInitializeConnections_Implementation(UVCamComponent* VCam) override;`
- L68 _private member_ `FChangeConnectionStateEvent OnPreStateChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Connections")` — Executes when the state is about to be changed
- L72 _private member_ `FChangeConnectionStateEvent OnPostStateChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Connections")` — Executes when after the state has been changed
- L76 _private member_ `TMap<FName, FVCamWidgetConnectionState> States { { DefaultState, {} } };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connections", meta = (AllowPrivateAccess = "true"))` — The states
- L79 _private member_ `FName CurrentState = DefaultState;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetCurrentState", BlueprintSetter = "K2_SetCurrentState", Category = "Connections")`
- L81 _private prototype_ `void SetStateOrFallbackToDefault(FName NewState, bool bReinitializeConnections = true);`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FChangeConnectionStateEvent, UVCamStateSwitcherWidget*, Widget, FName, OldState, FName, NewState);`
- L10 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FChangeConnectionStateEvent, UVCamStateSwitcherWidget*, Widget, FName, OldState, FName, NewState);`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamStateSwitcher, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamStateSwitcher, Log, All);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/UI/Switcher/VCamWidgetConnectionState.h` (Public)


#### struct `FVCamWidgetConnectionState`  
`struct FVCamWidgetConnectionState`  
_L11-18_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `TArray<FWidgetConnectionConfig> WidgetConfigs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")` — A list of widgets to update

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/UI/Switcher/WidgetConnectionConfig.h` (Public)


#### struct `FWidgetConnectionConfig`  
`struct FWidgetConnectionConfig`  
_L13-33_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `FVCamChildWidgetReference Widget;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")` — Defines the widget whose connections should be updated. Must be a VCamWidget. This is the name of a child widget and can be used as argument to UWidgetTree::FindWidget.
- L29 _public member_ `TMap<FName, FVCamConnectionTargetSettings> ConnectionTargets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")` — Key: A valid key of in UVCamWidget::Connections of the widget identified via WidgetProperty. Value: The settings to use for this connection.
- L31 _public prototype_ `UVCamWidget* ResolveWidget(UVCamStateSwitcherWidget* OwnerWidget) const;`
- L32 _public prototype_ `bool HasNoWidgetSet() const;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/UI/VCamConnectionStructs.h` (Public)


#### struct `FVCamConnectionTargetSettings`  
`struct FVCamConnectionTargetSettings`  
_L22-48_
- reflection: `USTRUCT(BlueprintType)`
- desc: This stores information about the target for a given VCam Widget Connection Ideally this is controlled externally via a configurator system but can be set explicitly if required
- L30 _public member_ `FName TargetModifierName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ConnectionBinding)` — The name of the Modifier to search for in a given VCam Component's Modifier Stack
- L36 _public member_ `FName TargetConnectionPoint = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ConnectionBinding)` — The name of the Connection Point to search for in a given VCam Modifier
- L38 _public function_ `bool operator==(const FVCamConnectionTargetSettings& Other) const`
- L44 _public function_ `bool HasValidSettings() const`

#### struct `FVCamConnection`  
`struct FVCamConnection`  
_L57-134_
- reflection: `USTRUCT(BlueprintType)`
- desc: A VCam Connection allows an external object (primarily widgets) to communicate with VCam Modifiers through Connection Points that have known properties. The connection allows you to specify a set of requirements that a connection point on a modifier must implement for it to be considered a valid thing to connect to and then a function "AttemptConnection" that will try to resolve a given VCam Component to a specific Modifier along with an optional associated Input Action
- L65 _public member_ `TArray<TSubclassOf<UInterface>> RequiredInterfaces;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Connection)` — A list of interfaces that a modifier must implement to be considered a valid connection
- L74 _public member_ `TArray<TSubclassOf<UInterface>> OptionalInterfaces;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Connection)` — A list of interfaces that a modifier may optionally implement that this connection can use These interfaces are not tested for when attempting a connection but are stored so that a Configurator system can provide extra information a user when they are configuring connections
- L80 _public member_ `bool bRequiresInputAction = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Connection)` — Whether this connection requires a target Connection Point to have an associated Input Action to be considered a valid connection
- L86 _public member_ `EInputActionValueType ActionType = EInputActionValueType::Boolean;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Connection, meta=(EditCondition="bRequiresInputAction"))` — If this connection requires an Input Action then this property specifies what Input Action Type the Connection Point must provide to be considered a valid connection
- L93 _public member_ `bool bManuallyConfigureConnection = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Connection)` — If you are not using an external system to configure the connection then you can enable this to have explicit control over which Modifier and Connection Point to look for when attempting a connection
- L99 _public member_ `FVCamConnectionTargetSettings ConnectionTargetSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Connection, meta=(EditCondition="bManuallyConfigureConnection", EditConditionHides))` — A struct containing information about which Modifier and Connection Point to look for when attempting a connection
- L107 _public member_ `TObjectPtr<UInputAction> ConnectedAction = nullptr;` — `UPROPERTY(Transient)` — The Input Action that we are currently connected to This could be empty even if we have a valid connection
- L115 _public member_ `TObjectPtr<UVCamModifier> ConnectedModifier = nullptr;` — `UPROPERTY(Transient)` — The VCam Modifier that we are currently connected to Guaranteed to be valid if IsConnected() is true
- L120 _public prototype_ `bool IsConnected() const;` — Check whether this connection was successfully connected to a Connection Point
- L125 _public prototype_ `bool AttemptConnection(UVCamComponent* VCamComponent);` — Attempts to make a connection to a target Connection Point and returns a bool indicating success
- L128 _public prototype_ `bool IsConnectionValid(UVCamModifier& Modifier, FName ConnectionPointName, bool bLogWarnings = false) const;` — Whether under the filter criteria of this struct it is legal to connection to ConnectionPoint from Modifier.
- L133 _public prototype_ `void ResetConnection();` — Clears any currently connected modifier and action

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamConnection, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamConnection, Log, All);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/UI/VCamUIFunctionLibrary.h` (Public)


#### class `UVCamUIFunctionLibrary`  
`class UVCamUIFunctionLibrary : public UBlueprintFunctionLibrary`  
_L17-73_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function Library primarily used for exposing functionality of UI related structs to Blueprints
- L27 _public prototype_ `static bool IsConnected_VCamConnection(const FVCamConnection& Connection);` — `UFUNCTION(BlueprintPure, Category = "VCam Connections", meta=(DisplayName = "Is Connected"))` — Checks whether a given VCam Connection is successfully connected. If this returns true then it is safe to assume that the Connected Modifier for the Connection is valid to use
- L34 _public prototype_ `static FName GetConnectionPointName_VCamConnection(const FVCamConnection& Connection);` — `UFUNCTION(BlueprintPure, Category = "VCam Connections", meta = (DisplayName = "Get Connection Point Name"))` — Gets the name of the associated Connection Point for a given VCam Connection. This will return "None" if the IsConnected() is false
- L41 _public prototype_ `static UVCamModifier* GetConnectedModifier_VCamConnection(const FVCamConnection& Connection);` — `UFUNCTION(BlueprintPure, Category = "VCam Connections", meta = (DisplayName = "Get Connected Modifier"))` — Gets the Connected Modifier for the given VCam Connection The returned Modifier is guaranteed to be valid if IsConnected() is true
- L50 _public prototype_ `static UInputAction* GetConnectedInputAction_VCamConnection(const FVCamConnection& Connection);` — `UFUNCTION(BlueprintPure, Category = "VCam Connections", meta = (DisplayName = "Get Connected Input Action"))` — Gets the Connected Input Action for the given VCam Connection The returned Input Action is only guaranteed to be valid if both IsConnected() is true AND the VCam Connection is set to require an Input Action If the VCam Connection doesn't require an Input Action then this may still return a valid Action if the Connection Point had an associated Input Action however you will need to test for this manually
- L56 _public prototype_ `static bool GetConnectionByName_VCamWidget(UVCamWidget* Widget, FName ConnectionId, FVCamConnection& OutConnection);` — `UFUNCTION(BlueprintPure, Category = "VCam Connections", meta = (DisplayName = "Get Connection By Name", DefaultToSelf = "Widget"))` — Gets a connection by its ID.
- L60 _public prototype_ `static bool IsConnected_VCamWidget(UVCamWidget* Widget, FName ConnectionId, bool& bOutIsConnected);` — `UFUNCTION(BlueprintPure, Category = "VCam Connections", meta = (DisplayName = "Is Connected By Name", DefaultToSelf = "Widget"))` — Gets whether the ConnectionId is connected on the widget.
- L64 _public prototype_ `static bool GetConnectionPointName_VCamWidget(UVCamWidget* Widget, FName ConnectionId, FName& OutConnectionPointName);` — `UFUNCTION(BlueprintPure, Category = "VCam Connections", meta = (DisplayName = "Get Connection Point Name By Name", DefaultToSelf = "Widget"))` — Gets the connection point the connection ConnectionId attempts to connect to on the widget.
- L68 _public prototype_ `static bool GetConnectedModifier_VCamWidget(UVCamWidget* Widget, FName ConnectionId, UVCamModifier*& OutModifier);` — `UFUNCTION(BlueprintPure, Category = "VCam Connections", meta = (DisplayName = "Get Connected Modifier By Name", DefaultToSelf = "Widget"))` — Gets the modifier connected to ConnectionId on the widget.
- L72 _public prototype_ `static bool GetConnectedInputAction_VCamWidget(UVCamWidget* Widget, FName ConnectionId, UInputAction*& OutInputAction);` — `UFUNCTION(BlueprintPure, Category = "VCam Connections", meta = (DisplayName = "Get Connected Input Action By Name", DefaultToSelf = "Widget"))` — Gets the input action mapped to ConnectionId on the widget.

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/UI/VCamWidget.h` (Public)


#### enum `EConnectionUpdateResult`  
`enum class EConnectionUpdateResult : uint8`  
_L14-18_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `DidUpdateConnections`
- L17 _public enumerator_ `NoConnectionsUpdated`

#### class `UVCamWidget`  
`class UVCamWidget : public UUserWidget`  
_L27-128_
- reflection: `UCLASS(Abstract)`
- inherits: `UUserWidget`
- desc: A wrapper widget class that contains a set of VCam Connections If you add a widget deriving from UVCamWidget to an Overlay Widget for a VCam Output Provider then when the Overlay is created by the Provider it will also call InitializeConnections with the owning VCam Component.
- L39 _public member_ `TMap<FName, FVCamConnection> Connections;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VCam Connections")` — The VCam Connections associated with this Widget Each Connection has a unique name associated with it and any connection related event will provide this name as one of its arguments.
- L47 _public member_ `bool bRegisterForInput = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="VCam Input")` — Determines whether this widget will be automatically registered to receive input when the connections are initialized Note: This property is only read during Initialize so toggling at runtime will not have any effect
- L53 _public member_ `TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="VCam Input", meta=(EditCondition="bRegisterForInput"))` — If this widget is registered for input then this input mapping context will be added to the input system
- L59 _public member_ `int32 InputContextPriority = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="VCam Input", meta=(EditCondition="bRegisterForInput"))` — If this widget is registered for input then this property defines the priority that the input mapping context is added at
- L61 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FConnectionsReinitializedDelegate);`
- L62 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConnectionsReinitializedDelegate_Blueprint);`
- L63 _public member_ `FConnectionsReinitializedDelegate OnPostConnectionsReinitializedDelegate;`
- L66 _public member_ `FConnectionsReinitializedDelegate_Blueprint OnPostConnectionsReinitializedDelegate_Blueprint;` — `UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnConnectionsReinitialized"))` — Called when ReinitializeConnections is called.
- L68 _public prototype_ `UVCamWidget(const FObjectInitializer& ObjectInitializer);`
- L71 _public prototype_ `virtual void NativePreConstruct() override;`
- L72 _public prototype_ `virtual void NativeDestruct() override;`
- L82 _public prototype_ `void OnConnectionUpdated(FName ConnectionName, bool bDidConnectSuccessfully, FName ModifierConnectionPointName, UVCamModifier* ConnectedModifier, UInputAction* ConnectedAction);` — `UFUNCTION(BlueprintImplementableEvent, Category="VCam Connections")` — Event called when a specific connection has been updated The connection is not guaranteed to succeed so "Did Connect Successfully" should be checked before using the connected modifier or action
- L88 _public prototype_ `void PostConnectionsInitialized();` — `UFUNCTION(BlueprintImplementableEvent, Category="VCam Connections")` — Event called after all connections have been initialized or reinitialized
- L94 _public prototype_ `void InitializeConnections(UVCamComponent* VCam);` — Iterate all VCam Connections within the widget and attempt to connect them using the provided VCam Component Optionally registers for input with the VCam Component if requested
- L101 _public prototype_ `bool ReinitializeConnections();` — `UFUNCTION(BlueprintCallable, Category="VCam Connections")` — Attempts to use the cached VCam Component to initialize the connections Returns true if there was a valid VCam Component to initialize with
- L112 _public prototype_ `void UpdateConnectionTargets(const TMap<FName, FVCamConnectionTargetSettings>& NewConnectionTargets, const bool bReinitializeOnSuccessfulUpdate, EConnectionUpdateResult& Result);` — `UFUNCTION(BlueprintCallable, Category="VCam Connections", meta=(ExpandEnumAsExecs="Result", bReinitializeOnSuccessfulUpdate=true))` — Looks through the set of Connections on this widget and if a matching connection name is found will attempt to update the connection target. If the new target is the same as the old target then no update is performed. This function will optionally reinitialize the widget connections if 1 or more targets were updated. Note: If a connection name in the NewConnectionTargets map is not found in the Widget Connections then it is ignored no new connections will be created and no connections will be removed
- L114 _public function_ `FORCEINLINE TObjectPtr<UVCamComponent> GetVCamComponent() const`
- L119 _protected prototype_ `void OnInitializeConnections(UVCamComponent* VCam);` — `UFUNCTION(BlueprintNativeEvent, Category = "VCam Connections")`
- L127 _private member_ `TObjectPtr<UVCamComponent> VCamComponent;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "VCam", meta = (AllowPrivateAccess = "true"))` — Cached pointer to the VCam Component that owns this VCam Widget

#### Free symbols / members of external scopes

- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE(FConnectionsReinitializedDelegate);`
- L62 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConnectionsReinitializedDelegate_Blueprint);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/UI/WidgetSnapshots.h` (Public)


#### struct `FWidgetSnapshot`  
`struct FWidgetSnapshot`  
_L11-21_
- reflection: `USTRUCT()`
- desc: Saves a subset of properties of a widget.
- L16 _public member_ `TSubclassOf<UUserWidget> WidgetClass;` — `UPROPERTY()`
- L20 _public member_ `TArray<uint8> SavedBinaryData;` — `UPROPERTY()` — Can be empty in case no properties were saved

#### struct `FWidgetTreeSnapshot`  
`struct FWidgetTreeSnapshot`  
_L25-42_
- reflection: `USTRUCT()`
- desc: Saves properties from widgets within a widget tree.
- L34 _public member_ `FName RootWidget = NAME_None;` — `UPROPERTY()` — The name of the root widget if it was saved (may not have passed filters). The root widget may be re-instanced (and thus renamed).
- L38 _public member_ `TMap<FName, FWidgetSnapshot> WidgetSnapshots;` — `UPROPERTY()` — Stores every widget in the hierarchy which passed filters, even if there are no properties to save.
- L40 _public function_ `void Reset()`
- L41 _public function_ `bool HasData() const`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Util/ConnectionUtils.h` (Public)


#### enum `UE::VCamCore::ConnectionUtils::EBreakBehavior`  
`enum class EBreakBehavior`  
_L26-34_
- L29 _public enumerator_ `Continue` — Continue with the next connection point or modifier
- L31 _public enumerator_ `SkipCurrentModifier` — Continue with the next connection point on the next modifier
- L33 _public enumerator_ `Break` — Stop

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace VCamCore` (scope `UE`)
- L11 _namespace_ `namespace ConnectionUtils` (scope `UE::VCamCore`)
- L14 _prototype_ `TArray<FModifierStackEntry> FindCompatibleModifiers(const FVCamConnection& Connection, UVCamComponent& Component);` (scope `UE::VCamCore::ConnectionUtils`) — Gets all modifiers that satisfy the connection's filter requirements and have at least one connection point available.
- L16 _function_ `FORCEINLINE TArray<FName> FindCompatibleModifierNames(const FVCamConnection& Connection, UVCamComponent& Component)` (scope `UE::VCamCore::ConnectionUtils`)
- L19 _function_ `Algo::Transform(FindCompatibleModifiers(Connection, Component), Result, [](const FModifierStackEntry& Entry){ return Entry.Name; });` (scope `UE::VCamCore::ConnectionUtils::FindCompatibleModifierNames`)
- L24 _prototype_ `TArray<FName> FindCompatibleConnectionPoints(const FVCamConnection& Connection, UVCamModifier& Modifier);` (scope `UE::VCamCore::ConnectionUtils`) — Gets all connection points that satisfy the connection's filter requirements.
- L35 _typedef_ `using FCompatibleModifierCallback = TFunctionRef<EBreakBehavior(const FModifierStackEntry& Modifier, FName ConnectionPoint)>;` (scope `UE::VCamCore::ConnectionUtils`)
- L37 _prototype_ `void ForEachCompatibleConnectionPoint(const FVCamConnection& Connection, const TArray<FModifierStackEntry>& Modifiers, FCompatibleModifierCallback ProcessConnectionPoint);` (scope `UE::VCamCore::ConnectionUtils`)
- L39 _function_ `FORCEINLINE void ForEachCompatibleConnectionPoint(const FVCamConnection& Connection, UVCamComponent& Component, FCompatibleModifierCallback ProcessConnectionPoint)` (scope `UE::VCamCore::ConnectionUtils`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Util/OutputProviderUtils.h` (Public)


#### enum `UE::VCamCore::ENameGenerationFlags`  
`enum class ENameGenerationFlags : uint8`  
_L20-30_
- desc: Flags for GenerateUniqueOutputProviderName.
- L22 _public enumerator_ `None`
- L29 _public enumerator_ `SkipAppendingIndex = 1 << 0` — The name should not contain the output provider index. The name is no longer guaranteed to be unique. Use this if you want the generated name to be the actor label or internal name depending on whether the actor label is unique.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace VCamCore` (scope `UE`)
- L14 _prototype_ `UVCamOutputProviderBase* GetOtherOutputProviderByIndex(const UVCamOutputProviderBase& OutputProvider, int32 Index);` (scope `UE::VCamCore`) — @return Gets the output provider at Index int the UVCamComponent that owns OutputProvider.
- L17 _prototype_ `int32 FindOutputProviderIndex(const UVCamOutputProviderBase& OutputProvider);` (scope `UE::VCamCore`) — @return Gets the index of OutputProvider in the UVCamComponent that owns OutputProvider.
- L31 _prototype_ `ENUM_CLASS_FLAGS(ENameGenerationFlags);` (scope `UE::VCamCore`)
- L40 _prototype_ `FString GenerateUniqueOutputProviderName(const UVCamOutputProviderBase& OutputProvider, ENameGenerationFlags Flags = ENameGenerationFlags::None);` (scope `UE::VCamCore`) — Generates a unique name for OutputProvider following the pattern %s_%d ([ActorLabel]_[OutputProviderIndex]) where - %s is the label of the owning actor if it is unique across all actors having a UVCamComponent in the world, and the owning actor's name otherwise - %d is the result of FindOutputProviderIndex @param OutputProvider The provider for which to generate the unique name @param Flags Flags to use for this operation

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Util/PromptClientForStringAsyncAction.h` (Public)


#### class `UPromptClientForStringAsyncAction`  
`class UPromptClientForStringAsyncAction : public UBlueprintAsyncActionBase`  
_L16-48_
- reflection: `UCLASS()`
- inherits: `UBlueprintAsyncActionBase`
- desc: Sends a prompt for a string to the current VCam client.
- L21 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStringPromptResponseDelegate, const FVCamStringPromptResponse&, Response);`
- L25 _public member_ `FStringPromptResponseDelegate OnCompleted;` — `UPROPERTY(BlueprintAssignable, Category = "VirtualCamera")` — Event that triggers when the operation completes.
- L35 _public prototype_ `static UPromptClientForStringAsyncAction* PromptClientForString(UVCamComponent* VCamComponent, FText PromptTitle, const FString& DefaultValue);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", meta = (BlueprintInternalUseOnly = "true"))` — Prompt the VCam client to provide a string value. @param VCamComponent The VCam component streaming video to the client. @param PromptTitle The title of the prompt to show to the user. If empty, a default title will be used. @param DefaultValue The default string to fill in the client's text box.
- L38 _public prototype_ `virtual void Activate() override;`
- L44 _private member_ `TObjectPtr<UVCamComponent> VCamComponent;` — `UPROPERTY(Transient)`
- L47 _private member_ `FVCamStringPromptRequest PromptRequest;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStringPromptResponseDelegate, const FVCamStringPromptResponse&, Response);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Util/UnifiedActivationDelegate.h` (Public)


#### struct `FVCamCoreChangeActivationArgs`  
`struct FVCamCoreChangeActivationArgs`  
_L13-20_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Can Activate Args"))`
- desc: Input struct for deciding whether an output provider can change its activation state.
- L19 _public member_ `TObjectPtr<UVCamOutputProviderBase> OutputProvider;` — `UPROPERTY(BlueprintReadWrite, Category = "Virtual Camera")` — The output provider that is about to be changed

#### struct `FVCamCoreChangeActivationResult`  
`struct FVCamCoreChangeActivationResult`  
_L24-35_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Can Activate Args"))`
- desc: Output struct for deciding whether an output provider can change its activation state.
- L30 _public member_ `bool bCanPerformOperation = true;` — `UPROPERTY(BlueprintReadWrite, Category = "Virtual Camera")` — Whether the activation change can take place
- L34 _public member_ `FText Reason = FText::GetEmpty();` — `UPROPERTY(BlueprintReadWrite, Category = "Virtual Camera")` — Optional reason to display if the operation is not valid.

#### struct `UE::VCamCore::FUnifiedActivationDelegate`  
`struct FUnifiedActivationDelegate`  
_L43-58_
- desc: Delegate for deciding whether an output provider can change its activation state.
- L45 _public typedef_ `using FActivationDelegateVariant = TVariant<TYPE_OF_NULLPTR, FCanChangeActiviationVCamDelegate, FCanChangeActiviationDynamicVCamDelegate>;`
- L47 _public member_ `FActivationDelegateVariant VariantDelegate;`
- L49 _public prototype_ `FUnifiedActivationDelegate() = default;`
- L50 _public function_ `FUnifiedActivationDelegate(FCanChangeActiviationVCamDelegate Delegate) : VariantDelegate(TInPlaceType<FCanChangeActiviationVCamDelegate>(), MoveTemp(Delegate))`
- L51 _public function_ `FUnifiedActivationDelegate(FCanChangeActiviationDynamicVCamDelegate Delegate) : VariantDelegate(TInPlaceType<FCanChangeActiviationDynamicVCamDelegate>(), MoveTemp(Delegate))`
- L53 _public prototype_ `FVCamCoreChangeActivationResult Execute(const FVCamCoreChangeActivationArgs& Args) const;`
- L54 _public prototype_ `bool IsBound() const;`
- L55 _public prototype_ `bool IsBoundToObject(FDelegateUserObjectConst InUserObject) const;`
- L57 _public function_ `void Unbind()`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FVCamCoreChangeActivationResult, FCanChangeActiviationVCamDelegate, const FVCamCoreChangeActivationArgs&);`
- L37 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FVCamCoreChangeActivationResult, FCanChangeActiviationVCamDelegate, const FVCamCoreChangeActivationArgs&);`
- L38 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FVCamCoreChangeActivationResult, FCanChangeActiviationDynamicVCamDelegate, const FVCamCoreChangeActivationArgs&, Args);`
- L38 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FVCamCoreChangeActivationResult, FCanChangeActiviationDynamicVCamDelegate, const FVCamCoreChangeActivationArgs&, Args);`
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace VCamCore` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Util/UnifiedActivationDelegateContainer.h` (Public)


#### class `UE::VCamCore::FUnifiedActivationDelegateContainer`  
`class FUnifiedActivationDelegateContainer`  
_L21-52_
- desc: Manages multiple FUnifiedActivationDelegates.
- L26 _public prototype_ `FDelegateHandle Add(FUnifiedActivationDelegate Delegate);` — Adds a delegate.
- L29 _public prototype_ `void Remove(const FDelegateHandle& Handle);` — Removes a previously bound delegate
- L31 _public prototype_ `void RemoveAll(FDelegateUserObjectConst UserObject);` — Removes all delegates bound to UserObject.
- L37 _public function_ `template<typename TConsumer> requires std::is_invocable_r_v<EBreakBehavior, TConsumer, const FUnifiedActivationDelegate&> void ForEach(TConsumer&& Consumer) const` — Iterates every delegate. It's unsafe to mutate the container during iteration.
- L51 _private member_ `TMap<FDelegateHandle, FUnifiedActivationDelegate> Delegates;` — The bound delegates

#### enum `UE::VCamCore::FUnifiedActivationDelegateContainer::EBreakBehavior`  
`enum class EBreakBehavior : uint8`  
_L33-33_
- L33 _public enumerator_ `enum class EBreakBehavior : uint8 { Continue, Break }; template<typename TConsumer> requires std::is_invocable_r_v<EBreakBehavior`
- L33 _public enumerator_ `enum class EBreakBehavior : uint8 { Continue, Break }; template<typename TConsumer> requires std::is_invocable_r_v<EBreakBehavior`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace VCamCore` (scope `UE`)
- L58 _prototype_ `TOptional<FVCamCoreChangeActivationResult> ExecuteUntilFailure(const FUnifiedActivationDelegateContainer& Container, const FVCamCoreChangeActivationArgs& Args);` (scope `UE::VCamCore`) — Executes all delegates in the container until the first FVCamCoreChangeActivationResult::bCanPerformOperation is false and returns that result. @return Result of the first FVCamCoreChangeActivationResult::bCanPerformOperation == false.

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Util/VCamCoreScriptingFunctionLibrary.h` (Public)


#### class `UVCamCoreScriptingFunctionLibrary`  
`class UVCamCoreScriptingFunctionLibrary : public UBlueprintFunctionLibrary`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L17 _public prototype_ `static void AddCanActivateOutputProviderDelegate(FCanChangeActiviationDynamicVCamDelegate Delegate);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Camera")` — Add a delegate with which you can decide whether an output provider can be activated.
- L21 _public prototype_ `static void RemoveCanActivateOutputProviderDelegate(UObject* Object);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Camera")` — Removes all activation deciding delegates you previously bound to the provider Object.

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Util/VCamViewportLocker.h` (Public)


#### struct `FVCamViewportLockState`  
`struct FVCamViewportLockState`  
_L9-16_
- reflection: `USTRUCT()`
- L15 _public member_ `bool bLockViewportToCamera = false;` — `UPROPERTY(EditAnywhere, Category = "Viewport")` — Whether the user wants the viewport to be locked

#### struct `FVCamViewportLocker`  
`struct FVCamViewportLocker`  
_L20-55_
- reflection: `USTRUCT()`
- desc: Keeps track of which viewports are locked
- L25 _public member_ `TMap<EVCamTargetViewportID, FVCamViewportLockState> Locks { { EVCamTargetViewportID::Viewport1, {} }, { EVCamTargetViewportID::Viewport2, {} }, { EVCamTargetViewportID::Viewport3, {} }, { EVCamTargetViewportID::Viewport4, {} } };` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Viewport")`
- L32 _public function_ `bool ShouldLock(EVCamTargetViewportID ViewportID) const`
- L37 _public function_ `FVCamViewportLocker& SetLockState(EVCamTargetViewportID ViewportID, bool bShouldLock)`

#### Free symbols / members of external scopes

- L43 _function_ `friend bool operator==(const FVCamViewportLocker& Left, const FVCamViewportLocker& Right)`
- L51 _function_ `friend bool operator!=(const FVCamViewportLocker& Left, const FVCamViewportLocker& Right)`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Util/WidgetReference.h` (Public)


#### struct `FChildWidgetReference`  
`struct FChildWidgetReference`  
_L14-30_
- reflection: `USTRUCT(BlueprintType)`
- desc: A reference to any child widget within an UMG Blueprint; only widgets in the same widget tree can be referenced. Has a detail customization for choosing widget.
- L26 _public member_ `TSoftObjectPtr<UWidget> Template;` — `UPROPERTY(EditAnywhere, Category = "Virtual Camera")` — Pointer to template widget within the Blueprint's widget tree. Important: in UMG there are templates and previews. Templates are like the CDO and previews are what you see in the editor @see FWidgetReference
- L28 _public prototype_ `UWidget* ResolveWidget(UUserWidget& OwnerWidget) const;`
- L29 _public function_ `bool HasNoWidgetSet() const`

#### struct `FVCamChildWidgetReference`  
`struct FVCamChildWidgetReference : public FChildWidgetReference`  
_L34-39_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FChildWidgetReference`
- desc: Version that restraints Widget to UVCamWidget instances.
- L38 _public function_ `UVCamWidget* ResolveVCamWidget(UUserWidget& OwnerWidget) const`

#### class `UWidgetReferenceBlueprintFunctionLibrary`  
`class UWidgetReferenceBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L42-58_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L48 _public function_ `static UWidget* ResolveWidget(const FChildWidgetReference& WidgetReference, UUserWidget* OwnerWidget)` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera")`
- L54 _public function_ `static UVCamWidget* ResolveVCamWidget(const FVCamChildWidgetReference& WidgetReference, UUserWidget* OwnerWidget)` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera")`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Util/WidgetTreeUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace VCamCore` (scope `UE`)
- L14 _prototype_ `void ForEachWidgetToConsiderForVCam(UUserWidget& Widget, TFunctionRef<void(UWidget*)> Callback);` (scope `UE::VCamCore`) — Calls the callback for each widget, including the children of UUserWidgets.
- L17 _prototype_ `UWidgetTree* GetWidgetTreeThroughBlueprintAsset(UUserWidget& Widget);` (scope `UE::VCamCore`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/VCamBaseActor.h` (Public)


#### class `AVCamBaseActor`  
`class AVCamBaseActor : public ACineCameraActor`  
_L15-29_
- reflection: `UCLASS(Abstract, Blueprintable, HideCategories = (Input, VCamComponent, SceneComponent), ShowCategories=("Input|MouseInput", "Input|TouchInput"), ComponentWrapperClass)`
- inherits: `ACineCameraActor`
- desc: Utility base class which sets up a UVCamComponent with a Cine Camera. Acts as base class for Blueprint VCamActor, which has some default properties set already. Therefore Abstract and NotPlaceable.
- L20 _public prototype_ `AVCamBaseActor(const FObjectInitializer& ObjectInitializer);`
- L23 _public function_ `UVCamComponent* GetVCamComponent() const` — `UFUNCTION(BlueprintPure, Category = VCam)`
- L28 _private member_ `TObjectPtr<UVCamComponent> VCamComponent = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = VCamBaseActor, BlueprintGetter = GetVCamComponent, meta = (DisplayAfter = "AutoActivateForPlayer", DisplayPriority = 1))`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/VCamComponent.h` (Public)


#### class `UVCamComponent`  
`class UVCamComponent : public USceneComponent`  
_L65-629_
- reflection: `UCLASS(Blueprintable, ClassGroup = VCam, HideCategories=(Mobility), meta=(BlueprintSpawnableComponent))`
- inherits: `USceneComponent`
- desc: Provides a modular system for editing a UCineCameraComponent using user widgets. This component must be attached as a direct child of UCineCameraComponent. This component implements a Model-View-Controller architecture where modifiers are the model, output providers the view, and this component the controller. There are three aspects to this component: - Modifiers implement logic for changing properties on the UCineCameraComponent. Modifiers contain ConnectionPoints. ConnectionPoints can optionally expose UInputActions (Enhanced Input) that can be invoked by widgets. - Output providers create and render widgets (possibly streaming them). Usually output providers create UVCamWidgets, which are special widgets that can connect to ConnectionPoints. Widgets interact with modifiers in two ways: - Simple: trigger input actions that modifiers are subscribed to and expose via connections. - Advanced: query whether modifiers implement certain custom defined interfaces. UVCamWidget Connections can be configured with required and optional interfaces. - UVCamSubsystems exist for as long as a UVCamComponent is enabled (this is comparable to ULocalPlayerSubsystem). One notable such system is the UInputVCamSubsystem which allows UVCamComponents to bind to input devices similarly to how APlayerControllers do in shipped games.
- L81 _public member_ `FOnComponentReplaced OnComponentReplaced;` — `UPROPERTY(BlueprintAssignable, Category = "VirtualCamera")` — There are situations in the editor where the component may be replaced by another component as part of the actor being reconstructed This event will notify you of that change and give you a reference to the new component. Bindings will be copied to the new component so you do not need to rebind this event Note: When the component is replaced you will need to get all properties on the component again such as Modifiers and Output Providers
- L84 _public prototype_ `virtual void OnComponentCreated() override;`
- L85 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L86 _public prototype_ `virtual void OnRegister() override;`
- L87 _public prototype_ `virtual void BeginDestroy() override;`
- L88 _public prototype_ `virtual void EndPlay(EEndPlayReason::Type Reason) override;`
- L89 _public prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;`
- L93 _public prototype_ `virtual void OnAttachmentChanged() override;`
- L97 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L98 _public prototype_ `virtual void PostLoad() override;`
- L99 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L103 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L104 _public prototype_ `virtual void CheckForErrors() override;`
- L105 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L106 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& PropertyAboutToChange) override;`
- L107 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L108 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L109 _public prototype_ `void OnOutputProvidersEdited(FPropertyChangedChainEvent& PropertyChangedEvent);`
- L113 _public prototype_ `void ApplyComponentInstanceData(FVCamComponentInstanceData& ComponentInstanceData, ECacheApplyPhase CacheApplyPhase);` — Applies the component instance cache
- L115 _public prototype_ `bool CanUpdate() const;`
- L116 _public prototype_ `void Update();`
- L121 _public prototype_ `void AddInputMappingContext(const UVCamModifier* Modifier);` — Adds the Input Mapping Context from a modifier, if it exists, to the input system
- L123 _public prototype_ `void RemoveInputMappingContext(const UVCamModifier* Modifier);` — Removes the Input Mapping Context from a modifier, if it exists, from the input system
- L125 _public prototype_ `void AddInputMappingContext(UInputMappingContext* Context, int32 Priority);` — Adds an explicitly provided Input Mapping Context to the input system
- L127 _public prototype_ `void RemoveInputMappingContext(UInputMappingContext* Context);` — Removes an explicitly provided Input Mapping Context to the input system
- L134 _public prototype_ `bool SetInputProfileFromName(const FName ProfileName);` — `UFUNCTION(BlueprintCallable, Category = "VCam Input")` — Attempts to apply key mapping settings from an input profile defined in VCam Input Settings Returns whether the profile was found and able to be applied
- L144 _public prototype_ `bool AddInputProfileWithCurrentlyActiveMappings(const FName ProfileName, bool bUpdateIfProfileAlreadyExists = true);` — `UFUNCTION(BlueprintCallable, Category="VCam Input", meta=(ReturnDisplayName = "Success"))` — Tries to add a new Input Profile to the VCam Input Settings and populates it with any currently active player mappable keys Note: The set of currently active player mappable keys may be larger than the set of mappings in this component's Input Profile Optionally this function can update an existing profile, this will only add any mappable keys that don't currently exist in the profile but will not remove any existing mappings Returns whether the profile was successfully added or updated
- L148 _public prototype_ `bool SaveCurrentInputProfileToSettings(const FName ProfileName) const;` — `UFUNCTION(BlueprintCallable, Category="VCam Input", meta=(ReturnDisplayName = "Success"))` — Saves the current input profile settings to the VCam Input Settings using the provided Profile Name
- L152 _public prototype_ `TArray<FEnhancedActionKeyMapping> GetAllPlayerMappableActionKeyMappings() const;` — `UFUNCTION(BlueprintCallable, Category="VCam Input", meta=(ReturnDisplayName = "PlayerMappableActionKeyMappings"))` — Searches the currently active input system for all registered key mappings that are marked as Player Mappable.
- L157 _public prototype_ `FKey GetPlayerMappedKey(const FName MappingName) const;` — `UFUNCTION(BlueprintCallable, Category="VCam Input", meta=(ReturnDisplayName = "Key"))` — Searches the currently active input system for the current key mapped to a given input mapping If there is not a player mapped key, then this will return EKeys::Invalid.
- L162 _public prototype_ `void SetEnabled(bool bNewEnabled);` — `UFUNCTION(BlueprintSetter)` — Sets whether the VCamComponent will update every frame
- L165 _public function_ `bool IsEnabled() const` — `UFUNCTION(BlueprintGetter)` — @return Whether the VCamComponent will update every frame
- L168 _public prototype_ `UCineCameraComponent* GetTargetCamera() const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L179 _public prototype_ `bool AddModifier(const FName Name, UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UVCamModifier> ModifierClass, UVCamModifier*& CreatedModif` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", Meta = (DeterminesOutputType = "ModifierClass", DynamicOutputParam = "CreatedModifier", ReturnDisplayName = "Success"))` — Add a modifier to the stack with a given name. If that name is already in use then the modifier will not be added. Returns the created modifier if the Add succeeded
- L187 _public prototype_ `bool InsertModifier(const FName Name, int32 Index, UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UVCamModifier> ModifierClass, UVCamModifier*& CreatedModif` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", Meta = (DeterminesOutputType = "ModifierClass", DynamicOutputParam = "CreatedModifier", ReturnDisplayName = "Success"))` — Insert a modifier to the stack with a given name and index. If that name is already in use then the modifier will not be added. The index must be between zero and the number of existing modifiers inclusive Returns the created modifier if the Add succeeded.
- L190 _public prototype_ `bool SetModifierIndex(int32 OriginalIndex, int32 NewIndex);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", Meta = (ReturnDisplayName = "Success"))` — Moves an existing modifier in the stack from its current index to a new index
- L194 _public prototype_ `void RemoveAllModifiers();` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Remove all Modifiers from the Stack.
- L197 _public prototype_ `bool RemoveModifier(const UVCamModifier* Modifier);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — @return Whether the modifier was removed successfully
- L200 _public prototype_ `bool RemoveModifierByIndex(const int ModifierIndex);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — @return Whether the modifier was removed successfully
- L203 _public prototype_ `bool RemoveModifierByName(const FName Name);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — @return Whether the modifier was removed successfully.
- L206 _public prototype_ `int32 GetNumberOfModifiers() const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L213 _public prototype_ `void GetAllModifiers(TArray<UVCamModifier*>& Modifiers) const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Returns all the Modifiers in the Component's Stack Note: It's possible not all Modifiers will be valid (such as if the user has not set a class for the modifier in the details panel)
- L217 _public prototype_ `TArray<FName> GetAllModifierNames() const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Returns all the modifier names used to identifying connection points.
- L219 _public function_ `const TArray<FModifierStackEntry>& GetModifierStack() const`
- L223 _public prototype_ `UVCamModifier* GetModifierByIndex(const int32 Index) const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Returns the Modifier in the Stack with the given index if it exist.
- L226 _public prototype_ `UVCamModifier* GetModifierByName(const FName Name) const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Tries to find a Modifier in the Stack with the given name. The returned Modifier must be checked before it is used.
- L229 _public prototype_ `void GetModifiersByClass(UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UVCamModifier> ModifierClass, TArray<UVCamModifier*>& FoundModifiers) c` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", Meta = (DeterminesOutputType = "ModifierClass", DynamicOutputParam = "FoundModifiers"))` — Given a specific Modifier class, returns a list of matching Modifiers
- L232 _public prototype_ `void GetModifiersByInterface(UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UInterface> InterfaceClass, TArray<UVCamModifier*>& FoundModifiers) c` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Given a specific Interface class, returns a list of matching Modifiers
- L240 _public prototype_ `void SetModifierContextClass(UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UVCamModifierContext> ContextClass, UVCamModifierContext*& CreatedCont` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", Meta = (DeterminesOutputType = "ContextClass", DynamicOutputParam = "CreatedContext", AllowAbstract = "false"))` — Sets the Modifier Context to a new instance of the provided class @param ContextClass The Class to create the context from @param CreatedContext The created Context, can be invalid if Context Class was None
- L247 _public prototype_ `UVCamModifierContext* GetModifierContext() const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Get the current Modifier Context @return Current Context
- L253 _public prototype_ `bool AddOutputProvider(UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UVCamOutputProviderBase> ProviderClass, UVCamOutputProviderBase*& CreatedProvi` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", Meta = (DeterminesOutputType = "ProviderClass", DynamicOutputParam = "CreatedProvider", ReturnDisplayName = "Success"))`
- L255 _public prototype_ `bool InsertOutputProvider(int32 Index, UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UVCamOutputProviderBase> ProviderClass, UVCamOutputProviderBase*& CreatedProvi` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", Meta = (DeterminesOutputType = "ProviderClass", DynamicOutputParam = "CreatedProvider", ReturnDisplayName = "Success"))`
- L258 _public prototype_ `bool SetOutputProviderIndex(int32 OriginalIndex, int32 NewIndex);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", Meta = (ReturnDisplayName = "Success"))` — Moves an existing Output Provider in the stack from its current index to a new index
- L261 _public prototype_ `void RemoveAllOutputProviders();` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L263 _public prototype_ `bool RemoveOutputProvider(const UVCamOutputProviderBase* Provider);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L265 _public prototype_ `bool RemoveOutputProviderByIndex(const int32 ProviderIndex);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L268 _public prototype_ `int32 GetNumberOfOutputProviders() const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L270 _public prototype_ `void GetAllOutputProviders(TArray<UVCamOutputProviderBase*>& Providers) const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L271 _public function_ `const TArray<TObjectPtr<UVCamOutputProviderBase>>& GetOutputProviders() const`
- L274 _public prototype_ `UVCamOutputProviderBase* GetOutputProviderByIndex(const int32 ProviderIndex) const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L276 _public prototype_ `void GetOutputProvidersByClass(UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UVCamOutputProviderBase> ProviderClass, TArray<UVCamOutputProviderBase*>& FoundProviders) c` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", Meta = (DeterminesOutputType = "ProviderClass", DynamicOutputParam = "FoundProviders"))`
- L279 _public prototype_ `void ApplyInputProfile();` — Call this after modifying the InputProfile in code to update the player mapped keys
- L283 _public prototype_ `bool GetLiveLinkDataForCurrentFrame(FLiveLinkCameraBlueprintData& LiveLinkData);` — `UFUNCTION(BlueprintCallable, Category="VirtualCamera")` — @return Whether LiveLinkData has a valid result.
- L294 _public prototype_ `void RegisterObjectForInput(UObject* Object);` — `UFUNCTION(BlueprintCallable, Category="VirtualCamera")` — Registers the given object with the VCamComponent's Input Component This allows dynamic input bindings such as input events in blueprints to work correctly Note: Ensure you call UnregisterObjectForInput when you are finished with the object otherwise input events will still fire until GC actually destroys the object @param Object The object to register
- L302 _public prototype_ `void UnregisterObjectForInput(UObject* Object) const;` — `UFUNCTION(BlueprintCallable, Category="VirtualCamera")` — Unregisters the given object with the VCamComponent's Input Component @param Object The object to unregister
- L310 _public prototype_ `TArray<FEnhancedActionKeyMapping> GetPlayerMappableKeys() const;` — `UE_DEPRECATED(5.3, "GetPlayerMappableKeys has been deprecated. Please use UEnhancedPlayerMappableKeyProfile::GetPlayerMappingRows instead.")` — `UFUNCTION(BlueprintCallable, Category="VirtualCamera", meta=(DeprecatedFunction, DeprecationMessage="GetPlayerMappableKeys has been deprecated. Please use UEnhancedPlayerMappableKeyProfile::GetPlayerMappingRows instead."))` — Returns a list of all player mappable keys that have been registered
- L317 _public prototype_ `virtual void InjectInputForAction(const UInputAction* Action, FInputActionValue RawValue, const TArray<UInputModifier*>& Modifiers, const TArray<UInputTrigger*>& Triggers);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", meta = (AutoCreateRefTerm = "Modifiers,Triggers"))` — Injects an input action.
- L323 _public prototype_ `virtual void InjectInputVectorForAction(const UInputAction* Action, FVector Value, const TArray<UInputModifier*>& Modifiers, const TArray<UInputTrigger*>& Triggers);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", meta = (AutoCreateRefTerm = "Modifiers,Triggers"))` — Injects an input vector for action.
- L330 _public function_ `FGameplayTag GetRole() const` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L332 _public function_ `void SetRole(FGameplayTag Value)` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L335 _public function_ `FLiveLinkSubjectName GetLiveLinkSubobject() const` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L337 _public function_ `void SetLiveLinkSubobject(FLiveLinkSubjectName Value)` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L340 _public function_ `bool GetDisableComponentWhenSpawnedBySequencer() const` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L342 _public function_ `void SetDisableComponentWhenSpawnedBySequencer(bool bValue)` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L345 _public function_ `bool GetRecordAsCineCamera() const` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L347 _public function_ `void SetRecordAsCineCamera(bool bValue)` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L350 _public function_ `bool GetDisableOutputOnMultiUserReceiver() const` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L352 _public function_ `void SetDisableOutputOnMultiUserReceiver(bool bValue)` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L355 _public function_ `const FVCamInputProfile& GetInputProfile() const` — `UFUNCTION(BlueprintPure, Category = "VCam Input")`
- L357 _public prototype_ `void SetInputProfile(const FVCamInputProfile& NewInputProfile);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="VirtualCamera")`
- L361 _public prototype_ `const FVCamInputDeviceConfig& GetInputDeviceSettings() const;` — `UFUNCTION(BlueprintPure, Category = "VCam Input")` — Gets the current input device settings being used (if this component is enabled) or that will be used (if not enabled).
- L364 _public prototype_ `void SetInputDeviceSettings(const FVCamInputDeviceConfig& NewInputProfile);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="VirtualCamera")` — Propagates devices settings all the way to the player input. Causes input to be filtered / consumed differently.
- L366 _public function_ `UInputComponent* GetInputComponent() const`
- L372 _public prototype_ `TArray<UVCamSubsystem*> GetSubsystemArray(const TSubclassOf<UVCamSubsystem>& Class) const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Gets all subsystems implementing this interface
- L376 _public prototype_ `UInputVCamSubsystem* GetInputVCamSubsystem() const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Gets the subsystem responsible for input handling.
- L379 _public function_ `template <typename TSubsystemClass> TSubsystemClass* GetSubsystem(const TSubclassOf<TSubsystemClass>& SubsystemClass) const`
- L384 _public function_ `bool IsInitialized() const` — Whether this component is initialized, i.e. the input subsystem is set up and the output providers are allowed to be active.
- L385 _public function_ `const FVCamViewportLocker& GetViewportLockState() const`
- L386 _public prototype_ `void SetViewportLockState(const FVCamViewportLocker& NewLockState);`
- L390 _public function_ `UWorld* GetVCamWorld() const` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Gets UWorld object from the vcam component
- L396 _private member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetEnabled, BlueprintGetter = IsEnabled, Category = "VirtualCamera", meta = (DisplayPriority = "1"))` — Whether the VCamComponent will update every frame
- L403 _private member_ `FGameplayTag Role;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetRole", BlueprintSetter = "SetRole", Category = "VirtualCamera", meta = (DisplayPriority = "2"))` — The role of this virtual camera.  If this value is set and the corresponding tag set on the editor matches this value, then this camera is the sender and the authority in the case when connected to a multi-user session.
- L407 _private member_ `FLiveLinkSubjectName LiveLinkSubject;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetLiveLinkSubobject", BlueprintSetter = "SetLiveLinkSubobject", Category="VirtualCamera", meta = (DisplayPriority = "3"))` — LiveLink subject name for the incoming camera transform
- L416 _private member_ `bool bLockViewportToCamera_DEPRECATED = false;` — `UPROPERTY()` — If true, render the viewport from the point of view of the parented CineCamera This was moved to UVCamOutputProvider::TargetViewport. See FVCamCoreCustomVersion::MoveTargetViewportFromComponentToOutput.
- L420 _private member_ `FVCamViewportLocker ViewportLocker;` — `UPROPERTY(EditAnywhere, Category = "VirtualCamera", meta = (DisplayPriority = "4"))` — Sync with output providers keeping track of which viewports are locked.
- L424 _private member_ `bool bDisableComponentWhenSpawnedBySequencer = true;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetDisableComponentWhenSpawnedBySequencer", BlueprintSetter = "SetDisableComponentWhenSpawnedBySequencer", Category = "VirtualCamera", meta = (AllowPrivateAccess = "true", DisplayPriority = "5"))` — If true, the component will force bEnabled to false when it is part of a spawnable in Sequencer
- L428 _private member_ `bool bRecordAsCineCamera = true;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetDisableComponentWhenSpawnedBySequencer", BlueprintSetter = "SetDisableComponentWhenSpawnedBySequencer", Category = "VirtualCamera", meta = (AllowPrivateAccess = "true", DisplayPriority = "5"))` — Affects recordings in Take Recorder. If true, the owning actor should be recorded as a spawnable ACineCameraActor. This allows you to disable the Virtual Camera plugin but still use the sequences taken by it.
- L432 _private member_ `bool bDisableOutputOnMultiUserReceiver = true;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetDisableOutputOnMultiUserReceiver", BlueprintSetter = "SetDisableOutputOnMultiUserReceiver", AdvancedDisplay, Category = "VirtualCamera", meta = (DisplayPriority = "6"))` — Do we disable the output if the virtual camera is in a Multi-user session and the camera is a "receiver" from multi-user
- L440 _private member_ `float UpdateFrequencyMs = 66.6f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="VirtualCamera", meta=(ForceUnits=ms, ClampMin = "11.0"), DisplayName="Update Frequencey")` — Indicates the frequency which camera updates are sent when in Multi-user mode. This has a minimum value of 11ms. Using values below 30ms is discouraged. When higher refresh rates are needed consider using LiveLink rebroadcast to stream camera data.
- L451 _public member_ `EVCamTargetViewportID TargetViewport_DEPRECATED = EVCamTargetViewportID::Viewport1;` — `UPROPERTY()` — Which viewport to use for this VCam. This was moved to UVCamOutputProvider::TargetViewport. See FVCamCoreCustomVersion::MoveTargetViewportFromComponentToOutput.
- L456 _private member_ `FVCamInputProfile InputProfile;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetInputProfile", BlueprintSetter = "SetInputProfile", Category = "VirtualCamera")`
- L459 _private member_ `FVCamInputDeviceConfig InputDeviceSettings;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetInputDeviceSettings", BlueprintSetter = "SetInputDeviceSettings", Category = "VirtualCamera")`
- L463 _private member_ `TArray<TObjectPtr<UVCamOutputProviderBase>> OutputProviders;` — `UPROPERTY(EditAnywhere, Instanced, Category = "VirtualCamera", meta = (AllowEditInlineCustomization, ShowInnerProperties))` — List of Output Providers (executed in order)
- L467 _private member_ `TObjectPtr<UVCamModifierContext> ModifierContext;` — `UPROPERTY(EditAnywhere, Instanced, Category = "VirtualCamera")` — Modifier Context object that can be accessed by the Modifier Stack
- L471 _private member_ `TArray<FModifierStackEntry> ModifierStack;` — `UPROPERTY(EditAnywhere, Category = "VirtualCamera")` — List of Modifiers (executed in order)
- L478 _private member_ `TObjectPtr<UInputComponent> InputComponent;` — `UPROPERTY(Transient, DuplicateTransient)` — From Ben H: Mark this as Transient/DuplicateTransient so that it is saved on the BP CDO and nowhere else and handled correctly during duplication operations (copy/paste etc)
- L482 _private member_ `TArray<TObjectPtr<UInputMappingContext>> AppliedInputContexts;` — `UPROPERTY(Transient, DuplicateTransient)` — Store the Input Mapping Contexts that have been added via this component
- L484 _private member_ `double LastEvaluationTime;`
- L486 _private member_ `TArray<UVCamOutputProviderBase*> SavedOutputProviders;`
- L487 _private member_ `TArray<FModifierStackEntry> SavedModifierStack;`
- L499 _private member_ `WasNotInitializedBeforePIE, } PIEMode = EPIEState::Normal;` — This VCam was not initialized when PIE was started hence it need to be re-initialized when PIE ends.
- L503 _private member_ `FObjectSubsystemCollection<UVCamSubsystem> SubsystemCollection;` — Initialize and deinitialize calls match our
- L506 _private member_ `bool bIsInitialized = false;` — Whether Initialize was called but not Deinitialize yet.
- L512 _private member_ `bool bHasInitedModifiers = false;` — Whether we've already iterated through all modifiers once and initialized them. True does not mean that all modifiers are actually initialized since the user can add objects through the details panel, which are initialized later by Update.
- L518 _private member_ `bool bHasInitedOutputProviders = false;` — Whether we've already iterated through all output providers  once and initialized them. True does not mean that all output providers are actually initialized since the user can add objects through the details panel, which are initialized later by Update.
- L524 _private prototype_ `void SetupVCamSystemsIfNeeded();` — Creates the InputComponent and binds global delegates. It is safe to call this multiple times.
- L525 _private prototype_ `void CleanupRegisteredDelegates();`
- L528 _private prototype_ `void LateInitForBlueprintCreatedVCam();` — Runs initialization logic for construction script created VCams.
- L531 _private prototype_ `void EnsureInitializedIfAllowed();` — Calls Initialize if not already initialized and this component is enabled.
- L533 _private prototype_ `virtual void Initialize();` — Initializes the input system, modifiers, output providers, and locks the viewport if needed.
- L535 _private prototype_ `void InitModifiers();` — Calls Initialize on all modifiers if this has not yet been done previously.
- L537 _private prototype_ `void InitOutputProviders();` — Calls Initialize on all output providers if this has not yet been done previously.
- L540 _private prototype_ `virtual void Deinitialize();` — De-initializes all systems initialized in Initialize().
- L543 _private prototype_ `void ReinitializeInput(TArray<TObjectPtr<UInputMappingContext>> InputContextsToReapply);` — Called as part of applying component instance data
- L545 _private prototype_ `void SyncInputSettings();`
- L547 _private prototype_ `void TickModifierStack(float DeltaTime);`
- L548 _private prototype_ `void TickOutputProviders(float DeltaTime);`
- L549 _private prototype_ `void TickSubsystems(float DeltaTime);`
- L551 _private prototype_ `static void CopyLiveLinkDataToCamera(const FLiveLinkCameraBlueprintData& LiveLinkData, UCineCameraComponent* CameraComponent);`
- L553 _private prototype_ `float GetDeltaTime();`
- L554 _private prototype_ `void UnlockAllViewports();`
- L555 _private prototype_ `void DestroyOutputProvider(UVCamOutputProviderBase* Provider);`
- L559 _private prototype_ `void ValidateModifierStack(const FString BaseName = "New` — Use the Saved Modifier Stack from PreEditChange to find the modified entry and then ensure the modified entry's name is unique If a new modifier has been created then its name will be defaulted to BaseName
- L560 _private prototype_ `bool DoesNameExistInSavedStack(const FName InName) const;`
- L561 _private prototype_ `void FindModifiedStackEntry(int32& ModifiedStackIndex, bool& bIsNewEntry) const;`
- L564 _private prototype_ `void OnMapChanged(UWorld* World, EMapChangeType ChangeType);`
- L566 _private prototype_ `void OnBeginPIE(const bool bInIsSimulating);`
- L567 _private prototype_ `void OnEndPIE(const bool bInIsSimulating);`
- L570 _private prototype_ `void HandleCameraComponentEventData(const FConcertSessionContext& InEventContext, const FMultiUserVCamCameraComponentEvent& InEvent);` — Multi-user support
- L572 _private prototype_ `void SessionStartup(TSharedRef<IConcertClientSession> InSession);`
- L573 _private prototype_ `void SessionShutdown(TSharedRef<IConcertClientSession> InSession);`
- L575 _private prototype_ `FString GetNameForMultiUser() const;`
- L577 _private prototype_ `void MultiUserStartup();`
- L578 _private prototype_ `void MultiUserShutdown();`
- L581 _private member_ `FDelegateHandle OnSessionStartupHandle;` — Delegate handle for a the callback when a session starts up
- L584 _private member_ `FDelegateHandle OnSessionShutdownHandle;` — Delegate handle for a the callback when a session shuts down
- L587 _private member_ `TWeakPtr<IConcertClientSession> WeakSession;` — Weak pointer to the client session with which to send events. May be null or stale.
- L589 _private member_ `double SecondsSinceLastLocationUpdate = 0;`
- L590 _private member_ `double PreviousUpdateTime = 0;`
- L594 _private prototype_ `void SendCameraDataViaMultiUser();` — Send the current camera state via Multi-user if connected and in a
- L597 _private prototype_ `bool ShouldUpdateOutputProviders() const;` — Can return false if we're in a multi-user session and the user configured us not to update.
- L599 _private prototype_ `bool ShouldEvaluateModifierStack() const;` — Can return false if we're in a multi-user session and the user configured us not to update.
- L600 _private prototype_ `bool IsMultiUserSession() const;`
- L601 _private prototype_ `bool IsCameraInVPRole() const;`
- L604 _private prototype_ `void HandleObjectReplaced(const TMap<UObject*, UObject*>& ReplacementMap);` — Detect when this instance replaces an old instance and calls NotifyComponentWasReplaced on the old instance.
- L606 _private prototype_ `void NotifyComponentWasReplaced(UVCamComponent* ReplacementComponent);` — When another component replaces us, get a notification so we can clean up
- L609 _private prototype_ `virtual void RegisterInputComponent();` — Utility functions for registering and unregistering our input component with the correct input system
- L610 _private prototype_ `virtual void UnregisterInputComponent();`
- L613 _private prototype_ `void RefreshInitializationState();` — Called after an undo, or applying instance cache. Calls Initialize or Deinitialize if needed based on bEnabled.
- L618 _private prototype_ `void OnPreSaveWorld(UWorld* World, FObjectPreSaveContext ObjectPreSaveContext);` — Removes the transient asset users data so it is not saved into the map.
- L620 _private prototype_ `void OnPostSaveWorld(UWorld* World, FObjectPostSaveContext ObjectPostSaveContext);` — Adds back the transient asset users data that was removed in OnPreSaveWorld.
- L623 _private prototype_ `void AddAssetUserDataConditionally();` — Adds UVCamBlueprintAssetUserData to this component if it was created by Blueprints. Allows detection of undoing placing the owning actor.
- L624 _private prototype_ `void RemoveAssetUserData();`
- L627 _private prototype_ `void OnAssetUserDataPostEditUndo();` — Deinitializes this VCam if the owning actor was removed by an undo operation.

#### enum `UVCamComponent::EPIEState`  
`enum class EPIEState`  
_L491-499_
- desc: Variable used for pausing update on editor objects while PIE is running
- L494 _public enumerator_ `Normal` — Default state when no PIE transition is needed.
- L496 _public enumerator_ `WasInitializedBeforePIE` — We de-initialized this VCam before starting PIE because it was initialized. Initialize this VCam when PIE ends.
- L498 _public enumerator_ `WasNotInitializedBeforePIE` — This VCam was not initialized when PIE was started hence it need to be re-initialized when PIE ends.

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamComponent, Log, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamComponent, Log, All);`
- L43 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComponentReplaced, UVCamComponent*, NewComponent);`
- L43 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComponentReplaced, UVCamComponent*, NewComponent);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/VCamComponentInstanceData.h` (Public)


#### struct `FVCamComponentInstanceData`  
`struct FVCamComponentInstanceData : public FSceneComponentInstanceData`  
_L15-50_
- reflection: `USTRUCT()`
- inherits: `FSceneComponentInstanceData`
- desc: Saves internal UVCamComponent state for Blueprint created components.
- L19 _public prototype_ `FVCamComponentInstanceData() = default;`
- L20 _public prototype_ `FVCamComponentInstanceData(const UVCamComponent* SourceComponent);`
- L22 _public prototype_ `virtual bool ContainsData() const override;`
- L23 _public prototype_ `virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override;`
- L24 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L30 _public member_ `TArray<TObjectPtr<UVCamOutputProviderBase>> StolenOutputProviders;` — These output providers are renamed and re-outered to the component they're applied to. The owning UVCamComponent makes sure to not reference the old instances in OnComponentDestroyed.
- L35 _public member_ `TArray<FModifierStackEntry> StolenModifiers;` — These output providers are renamed and re-outered to the component they're applied to. The owning UVCamComponent makes sure to not reference the old instances in OnComponentDestroyed.
- L38 _public member_ `TArray<TObjectPtr<UInputMappingContext>> AppliedInputContexts;` — Simple copy for carrying over player remappings
- L41 _public member_ `FLiveLinkSubjectName LiveLinkSubject;` — The subject name would be lost when the component is reconstructed so keep track of it.
- L44 _public member_ `bool bWasInitialized = false;` — The old value of bIsInitialized
- L46 _public member_ `bool bWereModifiersInitialized = false;` — The old value of bHasInitedModifiers
- L48 _public member_ `bool bWereOutputProvidersInitialized = false;` — The old value of bHasInitedOutputProviders

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/VCamCoreUserSettings.h` (Public)


#### class `UVirtualCameraCoreUserSettings`  
`class UVirtualCameraCoreUserSettings : public UObject`  
_L12-25_
- reflection: `UCLASS(config = VirtualCameraCore)`
- inherits: `UObject`
- desc: Virtual Camera Core User Settings
- L20 _public member_ `FString DiscoveryEndpoint = "23` — `UPROPERTY(config, EditAnywhere, Category = "Virtual Camera Core|Remote Discovery")` — The IP endpoint to listen to for app discovery messages.
- L24 _public member_ `int32 DiscoveryPort = 6667;` — `UPROPERTY(config, EditAnywhere, Category = "Virtual Camera Core|Remote Discovery")` — The port to listen to for app discovery messages.

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/VCamMultiUser.h` (Public)


#### struct `FMultiUserVCamCameraFocusData`  
`struct FMultiUserVCamCameraFocusData`  
_L19-49_
- reflection: `USTRUCT()`
- L24 _public prototype_ `FMultiUserVCamCameraFocusData() = default;`
- L25 _public prototype_ `FMultiUserVCamCameraFocusData(const UCineCameraComponent* InCineCameraComponent);`
- L27 _public prototype_ `FCameraFocusSettings ToCameraFocusSettings() const;`
- L30 _public member_ `float ManualFocusDistance = 100000.f;` — `UPROPERTY()`
- L32 _public member_ `float FocusSmoothingInterpSpeed = 8.f;` — `UPROPERTY()`
- L34 _public member_ `bool bSmoothFocusChanges = false;` — `UPROPERTY()`
- L37 _public member_ `FString ActorToTrack;` — `UPROPERTY()`
- L40 _public member_ `FVector RelativeOffset = FVector::ZeroVector;` — `UPROPERTY()`
- L43 _public member_ `ECameraFocusMethod FocusMethod = ECameraFocusMethod::DoNotOverride;` — `UPROPERTY()`
- L47 _public member_ `uint8 bDrawDebugFocusPlane : 1;` — `UPROPERTY()`

#### struct `FMultiUserVCamCameraData`  
`struct FMultiUserVCamCameraData`  
_L52-107_
- reflection: `USTRUCT()`
- L57 _public function_ `FMultiUserVCamCameraData() : CameraActorLocation(FVector::ZeroVector) , CameraActorRotation(FRotator::ZeroRotator) , CameraComponentLocation(FVector::ZeroVector) , CameraComponentRotation(FRotator::ZeroRotator) , CurrentAperture(0.f) , CurrentFocalLength(0.f) , bOverride_NearClipPlane(false) , bOverride_CameraISO(false) , CustomNearClipPlane(1.0f) , CameraISO(100.0f) , AutoExposureBias(1.0f)`
- L70 _public prototype_ `FMultiUserVCamCameraData(const AActor* InOwner, const UCineCameraComponent* InCineCameraComponent);`
- L72 _public prototype_ `void ApplyTo(AActor* InOwner, UCineCameraComponent* InCineCameraComponent) const;`
- L76 _public member_ `FVector CameraActorLocation;` — `UPROPERTY()` — Camera transform
- L78 _public member_ `FRotator CameraActorRotation;` — `UPROPERTY()`
- L80 _public member_ `FVector CameraComponentLocation;` — `UPROPERTY()`
- L82 _public member_ `FRotator CameraComponentRotation;` — `UPROPERTY()`
- L86 _public member_ `float CurrentAperture;` — `UPROPERTY()` — Camera settings
- L88 _public member_ `float CurrentFocalLength;` — `UPROPERTY()`
- L90 _public member_ `FMultiUserVCamCameraFocusData FocusSettings;` — `UPROPERTY()`
- L92 _public member_ `FCameraLensSettings LensSettings;` — `UPROPERTY()`
- L94 _public member_ `FCameraFilmbackSettings FilmbackSettings;` — `UPROPERTY()`
- L98 _public member_ `uint8 bOverride_NearClipPlane : 1;` — `UPROPERTY()` — Post process settings
- L100 _public member_ `uint8 bOverride_CameraISO:1;` — `UPROPERTY()`
- L102 _public member_ `float CustomNearClipPlane;` — `UPROPERTY()`
- L104 _public member_ `float CameraISO;` — `UPROPERTY()`
- L106 _public member_ `float AutoExposureBias;` — `UPROPERTY()`

#### struct `FMultiUserVCamCameraComponentEvent`  
`struct FMultiUserVCamCameraComponentEvent`  
_L114-126_
- reflection: `USTRUCT()`
- L121 _public member_ `FString TrackingName;` — `UPROPERTY()` — Name of the tracking camera
- L125 _public member_ `FMultiUserVCamCameraData CameraData;` — `UPROPERTY()` — Camera data

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/VCamSubsystem.h` (Public)


#### class `UVCamSubsystem`  
`class UVCamSubsystem : public USubsystem`  
_L12-22_
- reflection: `UCLASS(Abstract, Blueprintable, Within = VCamComponent)`
- inherits: `USubsystem`
- desc: Base class for auto instanced and initialized subsystem that share the lifetime of UVCamComponents.
- L18 _public prototype_ `UVCamComponent* GetVCamComponent() const;` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")`
- L21 _public function_ `virtual void OnUpdate(float DeltaTime)` — Called by UVCamComponent::Update (its equivalent of Tick).
