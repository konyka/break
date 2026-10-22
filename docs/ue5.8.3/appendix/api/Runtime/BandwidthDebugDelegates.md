# Runtime / BandwidthDebugDelegates

- module root: `Source/Runtime/Online/Experimental/BandwidthDebugDelegates`
- headers: 1; symbols: 15
- symbol kinds: class=2, delegate=2, macro=1, namespace=2, prototype=8
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Core

### `Source/Runtime/Online/Experimental/BandwidthDebugDelegates/Public/BandwidthDebugDelegates.h` (Public)


#### class `UClientBandwidthGlobalDelegates`  
`class UClientBandwidthGlobalDelegates : public UInterface`  
_L19-22_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IClientBandwidthGlobalDelegates`  
`class IClientBandwidthGlobalDelegates`  
_L24-40_
- L29 _public prototype_ `static void AddTextToDebugDisplay(FStringView CategoryName, FStringView TextToPrint, float Scale, FColor Color, bool bIsSubHeader = false);`
- L31 _public prototype_ `static FDelegateHandle BindToTextAdditionForDebugDisplay(TFunction<void(FStringView, FStringView, float, FColor, bool)> Callback);`
- L33 _public prototype_ `static void ClearDebugInfoForTick(FStringView CategoryName);`
- L35 _public prototype_ `static FDelegateHandle BindToClearDebugInfoForTick(TFunction<void(FStringView)> Callback);`
- L37 _public prototype_ `static void UnbindAllToClearDebugInfoForTick(FDelegateHandle Handle);`
- L39 _public prototype_ `static void UnbindAllToTextAdditionForDebugDisplay(FDelegateHandle Handle);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API BANDWIDTHDEBUGDELEGATES_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ClientBandwidthDelegates` (scope `UE`)
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnAdditionToDebugTextDisplay, FStringView, FStringView, float, FColor, bool);`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnAdditionToDebugTextDisplay, FStringView, FStringView, float, FColor, bool);` (scope `UE::ClientBandwidthDelegates`)
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClearForTick, FStringView);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClearForTick, FStringView);` (scope `UE::ClientBandwidthDelegates`)
