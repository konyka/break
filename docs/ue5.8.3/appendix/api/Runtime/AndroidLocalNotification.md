# Runtime / AndroidLocalNotification

- module root: `Source/Runtime/Android/AndroidLocalNotification`
- headers: 2; symbols: 22
- symbol kinds: class=1, delegate=1, member=4, namespace=2, prototype=11, struct=1, typedef=1, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Launch
- PublicIncludePathModuleNames: AndroidLocalNotification, Engine

### `Source/Runtime/Android/AndroidLocalNotification/Private/AndroidJniLocalNotification.h` (Private)


#### struct `UE::Jni::FLocalNotification`  
`struct FLocalNotification`  
_L11-21_
- L13 _public typedef_ `using PartialClass = FGameActivity;`
- L15 _public prototype_ `static void JNICALL nativeAppOpenedWithLocalNotification(JNIEnv* env, jobject thiz, jstring jactivationEvent, int32 jFireDate);`
- L17 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(nativeAppOpenedWithLocalNotification) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L23 _variable_ `template struct TInitialize<FLocalNotification>;` (scope `UE::Jni`)

### `Source/Runtime/Android/AndroidLocalNotification/Public/AndroidLocalNotification.h` (Public)


#### class `FAndroidLocalNotificationService`  
`class FAndroidLocalNotificationService : public ILocalNotificationService`  
_L23-41_
- inherits: `ILocalNotificationService`
- desc: AndroidLocalNotification implementation of an Unreal local notification service.
- L26 _public prototype_ `FAndroidLocalNotificationService();`
- L28 _public prototype_ `virtual void ClearAllLocalNotifications();`
- L29 _public prototype_ `virtual int32 ScheduleLocalNotificationAtTime(const FDateTime& FireDateTime, bool LocalTime, const FText& Title, const FText& Body, const FText& Action, const FString& ActivationEvent);`
- L30 _public prototype_ `virtual int32 ScheduleLocalNotificationAtTimeOverrideId(const FDateTime& FireDateTime, bool LocalTime, const FText& Title, const FText& Body, const FText& Action, const FString& ActivationEvent, int32 IdOverride);`
- L31 _public prototype_ `virtual int32 ScheduleLocalNotificationBadgeAtTime(const FDateTime& FireDateTime, bool LocalTime, const FString& ActivationEvent);`
- L32 _public prototype_ `virtual void GetLaunchNotification(bool& NotificationLaunchedApp, FString& ActivationEvent, int32& FireDate);`
- L33 _public prototype_ `virtual void SetLaunchNotification(FString const& ActivationEvent, int32 FireDate);`
- L34 _public prototype_ `virtual void CancelLocalNotification(const FString& ActivationEvent);`
- L35 _public prototype_ `virtual void CancelLocalNotification(int NotificationId);`
- L38 _private member_ `bool AppLaunchedWithNotification;`
- L39 _private member_ `FString LaunchNotificationActivationEvent;`
- L40 _private member_ `int32 LaunchNotificationFireDate;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidLocalNotification, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidLocalNotification, Log, All);`
