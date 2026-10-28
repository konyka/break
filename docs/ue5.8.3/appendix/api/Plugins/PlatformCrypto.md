# Plugins / PlatformCrypto

- module root: `Plugins/Experimental/PlatformCrypto/Source/PlatformCrypto`
- headers: 2; symbols: 6
- symbol kinds: class=1, function=2, prototype=3
- PublicDependencyModuleNames: Core, PlatformCryptoContext, PlatformCryptoTypes

### `Plugins/Experimental/PlatformCrypto/Source/PlatformCrypto/Public/IPlatformCrypto.h` (Public)


#### class `IPlatformCrypto`  
`class IPlatformCrypto : public IModuleInterface`  
_L11-59_
- inherits: `IModuleInterface`
- desc: Entry point for cryptographic functionality.
- L19 _public prototype_ `virtual void StartupModule() override;` — Called when crytpo module is loaded
- L24 _public prototype_ `virtual void ShutdownModule() override;` — Called when crytpo module is unloaded
- L32 _public function_ `static inline IPlatformCrypto& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L50 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L58 _public prototype_ `TUniquePtr<FEncryptionContext> CreateContext();` — Creates and returns an encryption context object appropriate for the platform.

### `Plugins/Experimental/PlatformCrypto/Source/PlatformCrypto/Public/PlatformCryptoIncludes.h` (Public)
_(no declarations extracted)_
