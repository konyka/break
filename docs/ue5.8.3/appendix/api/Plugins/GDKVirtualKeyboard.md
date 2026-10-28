# Plugins / GDKVirtualKeyboard

- module root: `Plugins/Runtime/Microsoft/GDKVirtualKeyboard/Source/GDKVirtualKeyboard`
- headers: 1; symbols: 10
- symbol kinds: class=1, member=3, prototype=6

### `Plugins/Runtime/Microsoft/GDKVirtualKeyboard/Source/GDKVirtualKeyboard/Public/GDKPlatformTextField.h` (Public)


#### class `FGDKPlatformTextField`  
`class FGDKPlatformTextField : public IPlatformTextField`  
_L10-27_
- inherits: `IPlatformTextField`
- L13 _public prototype_ `FGDKPlatformTextField();`
- L14 _public prototype_ `~FGDKPlatformTextField();`
- L16 _public prototype_ `virtual void ShowVirtualKeyboard(bool bShow, int32 UserIndex, TSharedPtr<IVirtualKeyboardEntry> TextEntryWidget) override;`
- L19 _private prototype_ `void VirtualKeyboardCallbackBackgroundThread(TWeakPtr<IVirtualKeyboardEntry> WeakTextEntryWidget, FString StringResult, ETextEntryType EntryType);`
- L20 _private prototype_ `void VirtualKeyboardCallbackGameThread(TWeakPtr<IVirtualKeyboardEntry> WeakTextEntryWidget, FString StringResult, ETextEntryType EntryType);`
- L22 _private prototype_ `void KillExisitingDialog();`
- L24 _private member_ `FCriticalSection AsyncBlockCrit;`
- L25 _private member_ `TUniquePtr<FGDKAsyncBlock> KeyboardAsyncBlock;`
- L26 _private member_ `double DebounceTime;`
