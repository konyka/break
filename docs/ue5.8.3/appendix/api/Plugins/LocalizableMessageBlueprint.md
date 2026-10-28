# Plugins / LocalizableMessageBlueprint

- module root: `Plugins/Experimental/LocalizableMessage/Source/LocalizableMessageBlueprint`
- headers: 1; symbols: 5
- symbol kinds: class=1, prototype=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, LocalizableMessage

### `Plugins/Experimental/LocalizableMessage/Source/LocalizableMessageBlueprint/Public/LocalizableMessageLibrary.h` (Public)


#### class `ULocalizableMessageLibrary`  
`class ULocalizableMessageLibrary : public UBlueprintFunctionLibrary`  
_L14-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: BlueprintFunctionLibrary for LocalizableMessage
- L23 _public prototype_ `static FText Conv_LocalizableMessageToText(UObject* WorldContextObject, UPARAM(ref) const FLocalizableMessage& Message);` — `UFUNCTION(BlueprintPure, Category = "Localizable Message", meta = (WorldContext = "WorldContextObject"))` — Conversion function from LocalizableMessage to FText.
- L29 _public prototype_ `static bool EqualEqual_LocalizableMessage(UPARAM(ref) const FLocalizableMessage& A, UPARAM(ref) const FLocalizableMessage& B);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Localizable Message", meta = (DisplayName = "Equal (LocalizableMessage)", CompactNodeTitle = "==", BlueprintThreadSafe))` — Returns true if the Localizable Messages are equal (A == B)
- L35 _public prototype_ `static bool IsEmpty_LocalizableMessage(UPARAM(ref) const FLocalizableMessage& Message);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Localizable Message")` — Returns true if the message is empty
- L41 _public prototype_ `static void Reset_LocalizableMessage(UPARAM(ref) FLocalizableMessage& Message);` — `UFUNCTION(BlueprintCallable, Category = "Localizable Message")` — Resets the Localizable Message
