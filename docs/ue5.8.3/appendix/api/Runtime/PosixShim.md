# Runtime / PosixShim

- module root: `Source/Runtime/PlatformThirdPartyHelpers/PosixShim`
- headers: 2; symbols: 2
- symbol kinds: class=1, prototype=1
- PublicDependencyModuleNames: Core

### `Source/Runtime/PlatformThirdPartyHelpers/PosixShim/Public/PosixShim.h` (Public)


#### Free symbols / members of external scopes

- L15 _prototype_ `void SetPosixShimUTCServerTime(const FDateTime UTCServerTime);` — Sets the current UTC server time.  This value should be set from a trusted-to-be-roughly-correct source, and should be updated from time to time. @param UTCServerTime The new server time

### `Source/Runtime/PlatformThirdPartyHelpers/PosixShim/Public/PosixShimModule.h` (Public)


#### class `IPosixShimModule`  
`class IPosixShimModule : public IModuleInterface`  
_L12-14_
- inherits: `IModuleInterface`
- desc: PosixShimModule interface
