# Runtime / EyeTracker

- module root: `Source/Runtime/EyeTracker`
- headers: 4; symbols: 46
- symbol kinds: class=3, enum=1, enumerator=3, function=7, macro=1, member=14, prototype=14, struct=3
- PrivateDependencyModuleNames: Analytics, Core, CoreUObject, Engine, InputCore, RHI, RenderCore, Renderer, Slate, SlateCore

### `Source/Runtime/EyeTracker/Public/EyeTrackerFunctionLibrary.h` (Public)


#### class `UEyeTrackerFunctionLibrary`  
`class UEyeTrackerFunctionLibrary : public UBlueprintFunctionLibrary`  
_L15-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static bool IsEyeTrackerConnected();` — `UFUNCTION(BlueprintPure, Category = "Eye Tracking")` — Returns whether or not the eye-tracking hardware is connected and ready to use. It may or may not actually be in use. @return (Boolean)  true if eye tracker is connected and ready to use, false otherwise
- L33 _public prototype_ `static bool IsStereoGazeDataAvailable();` — `UFUNCTION(BlueprintPure, Category = "Eye Tracking")` — Returns whether or not the eye-tracking hardware is connected and ready to use. It may or may not actually be in use. @return true if the connected eye tracker supports per-eye gaze data, false otherwise
- L41 _public prototype_ `static bool GetGazeData(FEyeTrackerGazeData& OutGazeData);` — `UFUNCTION(BlueprintCallable, Category = "Eye Tracking")` — Returns unfied gaze data from the eye tracker. This is a single gaze ray, representing the fusion of both eyes. @param PlayerController		The player for whom we are tracking. Null can be ok for some devices, but this may be necessary for others to determine viewport properties, etc. @return						True if the returned gaze data is valid, false otherwise. A false return is likely to be common (e.g. the when user blinks).
- L49 _public prototype_ `static bool GetStereoGazeData(FEyeTrackerStereoGazeData& OutGazeData);` — `UFUNCTION(BlueprintCallable, Category = "Eye Tracking")` — Returns stereo gaze data from the eye tracker. This includes a gaze ray per eye, as well as a fixation point. @param PlayerController		The player for whom we are tracking. Null can be ok for some devices, but this may be necessary for others to determine viewport properties, etc. @return						True if the returned gaze data is valid, false otherwise. A false return is likely to be common (e.g. the when user blinks).
- L56 _public prototype_ `static void SetEyeTrackedPlayer(APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, Category = "Eye Tracking")` — Specifies player being eye-tracked. This is not necessary for all devices, but is necessary for some to determine viewport properties, etc. @param PlayerController		The player for whom we are tracking. Null can be ok for some devices, but this may be necessary for others to determine viewport properties, etc.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API EYETRACKER_API`

### `Source/Runtime/EyeTracker/Public/EyeTrackerTypes.h` (Public)


#### struct `FEyeTrackerGazeData`  
`struct FEyeTrackerGazeData`  
_L23-71_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a unified gaze ray that incorporates both eyes.
- L29 _public function_ `FEyeTrackerGazeData() : GazeOrigin(ForceInitToZero) , GazeDirection(ForceInitToZero) , FixationPoint(ForceInitToZero) , ConfidenceValue(0.f) , bIsLeftEyeBlink(false) , bIsRightEyeBlink(false) , LeftPupilDiameter(0.0f) , RightPupilDiameter(0.0f)`
- L42 _public member_ `FVector GazeOrigin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gaze Data")` — Origin of the unified gaze ray.
- L46 _public member_ `FVector GazeDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gaze Data")` — Forward direction of the unified gaze ray.
- L50 _public member_ `FVector FixationPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gaze Data")` — Location that the eyes converge. This is the 3d point where the tracked viewer is looking.
- L54 _public member_ `float ConfidenceValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gaze Data")` — Value [0..1] that represents confidence in the gaze ray data above. Stable, reliably tracked eyes will be at or near 1. Fast-moving or unreliably tracked eyes will be at or near 0.
- L58 _public member_ `bool bIsLeftEyeBlink;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gaze Data")` — Left eye blink data. True if the eye is close. False if the eye is open.
- L62 _public member_ `bool bIsRightEyeBlink;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gaze Data")` — Right eye blink data. True if the eye is close. False if the eye is open.
- L66 _public member_ `float LeftPupilDiameter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gaze Data")` — Diameter of the left pupil.
- L70 _public member_ `float RightPupilDiameter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gaze Data")` — Diameter of the right pupil

#### struct `FEyeTrackerStereoGazeData`  
`struct FEyeTrackerStereoGazeData`  
_L79-116_
- reflection: `USTRUCT(BlueprintType)`
- desc: Stereo gaze data that contains information for each eye individually. This may not be available with all devices.
- L85 _public function_ `FEyeTrackerStereoGazeData() : LeftEyeOrigin(ForceInitToZero) , LeftEyeDirection(ForceInitToZero) , RightEyeOrigin(ForceInitToZero) , RightEyeDirection(ForceInitToZero) , FixationPoint(ForceInitToZero) , ConfidenceValue(0.f)`
- L96 _public member_ `FVector LeftEyeOrigin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stereo Gaze Data")` — Origin of the left eye's gaze ray.
- L99 _public member_ `FVector LeftEyeDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stereo Gaze Data")` — Forward direction of the left eye's gaze ray.
- L103 _public member_ `FVector RightEyeOrigin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stereo Gaze Data")` — Origin of the right eye's gaze ray.
- L106 _public member_ `FVector RightEyeDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stereo Gaze Data")` — Forward direction of the right eye's gaze ray.
- L110 _public member_ `FVector FixationPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stereo Gaze Data")` — Location that the eyes converge. This is the 3d point where the tracked viewer is looking.
- L114 _public member_ `float ConfidenceValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stereo Gaze Data")` — Value [0..1] that represents confidence in the gaze ray data above. Stable, reliably tracked eyes will be at or near 1. Fast-moving or unreliably tracked eyes will be at or near 0.

#### enum `EEyeTrackerStatus`  
`enum class EEyeTrackerStatus : uint8`  
_L119-127_
- reflection: `UENUM(BlueprintType)`
- L122 _public enumerator_ `NotConnected` — Eyetracking feature is not available (device not plugged in, etc)
- L124 _public enumerator_ `NotTracking` — Eyetracking is operating, but eyes are not being tracked
- L126 _public enumerator_ `Tracking` — Eyetracking is operating and eyes are being tracked

### `Source/Runtime/EyeTracker/Public/IEyeTracker.h` (Public)


#### class `IEyeTracker`  
`class IEyeTracker`  
_L11-38_
- L19 _public prototype_ `virtual void SetEyeTrackedPlayer(APlayerController* PlayerController) = 0;` — Specifies player being eye-tracked. This is not necessary for all devices, but is necessary for some to determine viewport properties, etc.. Implementing class should cache this locally as it doesn't need to be called every tick.
- L25 _public prototype_ `virtual bool GetEyeTrackerGazeData(FEyeTrackerGazeData& OutGazeData) const = 0;` — Returns gaze data for the given player controller. @return true if returning valid data, false if gaze data was unavailable
- L31 _public prototype_ `virtual bool GetEyeTrackerStereoGazeData(FEyeTrackerStereoGazeData& OutGazeData) const = 0;` — Returns stereo gaze data for the given player controller (contains data for each eye individually). @return true if returning valid data, false if stereo gaze data was unavailable
- L34 _public prototype_ `virtual EEyeTrackerStatus GetEyeTrackerStatus() const = 0;` — Returns information about the status of the current device.
- L37 _public prototype_ `virtual bool IsStereoGazeDataAvailable() const = 0;` — Returns true if the current device can provide per-eye gaze data, false otherwise.

### `Source/Runtime/EyeTracker/Public/IEyeTrackerModule.h` (Public)


#### class `IEyeTrackerModule`  
`class IEyeTrackerModule : public IModuleInterface, public IModularFeature`  
_L14-80_
- inherits: `IModuleInterface,IModularFeature`
- desc: The public interface of the EyeTracker module
- L18 _public prototype_ `static FName GetModularFeatureName();` — Returns modular feature name for this module
- L20 _public prototype_ `virtual FString GetModuleKeyName() const = 0;`
- L25 _public function_ `float GetModulePriority() const` — #todo jcf: need to work out prioritization and selection scheme e.g. it doesn't ever really make sense to choose a desktop eye tracker if in VR mode?
- L47 _public function_ `static inline IEyeTrackerModule& Get()` — Singleton-like access to IEyeTrackerModule @return Returns reference to the highest priority IEyeTrackerModule module
- L59 _public function_ `static inline bool IsAvailable()` — Checks to see if there exists a module registered as an EyeTracker.  It is only valid to call Get() if IsAvailable() returns true. @return True if there exists a module registered as an HMD.
- L67 _public function_ `virtual void StartupModule() override` — Register module as an EyeTracker on startup.
- L72 _public prototype_ `virtual bool IsEyeTrackerConnected() const = 0;`
- L79 _public prototype_ `virtual TSharedPtr< class IEyeTracker, ESPMode::ThreadSafe > CreateEyeTracker() = 0;` — Attempts to create a new head tracking device interface @return	Interface to the new head tracking device, if we were able to successfully create one

#### struct `IEyeTrackerModule::FCompareModulePriority`  
`struct FCompareModulePriority`  
_L34-40_
- desc: Sorting method for which plug-in should be given priority
- L36 _public function_ `bool operator()(IEyeTrackerModule& A, IEyeTrackerModule& B) const`
