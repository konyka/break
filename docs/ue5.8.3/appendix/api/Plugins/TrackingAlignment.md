# Plugins / TrackingAlignment

- module root: `Plugins/VirtualProduction/CameraCalibration/Source/TrackingAlignment`
- headers: 4; symbols: 17
- symbol kinds: class=2, member=7, prototype=6, struct=2
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, OpenCV, OpenCVHelper

### `Plugins/VirtualProduction/CameraCalibration/Source/TrackingAlignment/Private/TrackingAlignmentActors.h` (Private)


#### struct `FTrackingAlignmentActors`  
`struct FTrackingAlignmentActors`  
_L11-22_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct of Source and Origin actors from a single Tracking space used for Space alignment.
- L17 _public member_ `TSoftObjectPtr<AActor> SourceActor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracking Alignment")` — Tracked source actor in the tracking space.
- L21 _public member_ `TSoftObjectPtr<AActor> OriginActor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracking Alignment")` — Tracked origin actor in the tracking space.

### `Plugins/VirtualProduction/CameraCalibration/Source/TrackingAlignment/Private/TrackingAlignmentBPLibrary.h` (Private)


#### class `UTrackingAlignmentFunctionLibrary`  
`class UTrackingAlignmentFunctionLibrary : public UBlueprintFunctionLibrary`  
_L16-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint functions to caluclate tracking space alignment.
- L23 _public prototype_ `static int32 GetMinimumRequiredTrackerAligmentSampleCount();` — `UFUNCTION(BlueprintPure, Category = "Tracking Alignment")` — Gets the minimum number of require tracker alignment samples to be able to calculate a Cam2Base value.
- L30 _public prototype_ `static FTransform GetAlignedTrackerBOrigin(UTrackingAlignmentCalibrationProfile* InCalibrationProfile);` — `UFUNCTION(BlueprintCallable, Category = "Tracking Alignment")` — Given a UTrackingAlignmentCalibrationProfile, returns the calculated alignment origin for TrackerB space to Tracker A space. Uses OpenCV to solve the space alignment using Eye-To-Hand calibration with the given calibration method.
- L34 _public prototype_ `static bool FindAndUpdateOriginActor(UPARAM(ref) FTrackingAlignmentActors& InTrackingActors, AActor*& OutNewParentActor);` — `UFUNCTION(BlueprintCallable, Category = "Tracking Alignment")` — Given an actor being tracked, find and update its origin actor to the direct parent actor.

### `Plugins/VirtualProduction/CameraCalibration/Source/TrackingAlignment/Private/TrackingAlignmentCalibrationProfile.h` (Private)


#### class `UTrackingAlignmentCalibrationProfile`  
`class UTrackingAlignmentCalibrationProfile : public UPrimaryDataAsset`  
_L14-42_
- reflection: `UCLASS(MinimalAPI, BlueprintType, AutoExpandCategories = ("Tracking Alignment"))`
- inherits: `UPrimaryDataAsset`
- desc: Calibration profile holding actors and samples for aligning two tracking spaces.
- L21 _public member_ `FTrackingAlignmentActors TrackerAActors;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracking Alignment")` — Tracking space A tracked source and origin actor.
- L25 _public member_ `FTrackingAlignmentActors TrackerBActors;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracking Alignment")` — Tracking space B tracked source and origin actor.
- L29 _public member_ `TArray<FTrackingAlignmentSample> Samples;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Tracking Alignment")` — Captured samples from both Tracking space A and B.
- L33 _public prototype_ `bool CaptureSample(FTrackingAlignmentSample& NewSample);` — `UFUNCTION(BlueprintCallable, Category = "Tracking Alignment")` — Capture and add a new sample for TrackerAActors and TrackerBActors, and write it into the out parameter NewSample.
- L37 _public prototype_ `bool RemoveSample(int32 AtIndex);` — `UFUNCTION(BlueprintCallable, Category = "Tracking Alignment")` — Remove sample at the given index.
- L41 _public prototype_ `void ClearSamples();` — `UFUNCTION(BlueprintCallable, Category = "Tracking Alignment")` — Clear all current samples.

### `Plugins/VirtualProduction/CameraCalibration/Source/TrackingAlignment/Private/TrackingAlignmentSample.h` (Private)


#### struct `FTrackingAlignmentSample`  
`struct FTrackingAlignmentSample`  
_L12-23_
- reflection: `USTRUCT(BlueprintType)`
- desc: Single sample as part of a Tracking Alignment calibration, holding transform samples from both Tracking space A and B.
- L18 _public member_ `FTransform TransformA;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Tracking Alignment")` — Transform sample from Tracking Space A.
- L22 _public member_ `FTransform TransformB;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Tracking Alignment")` — Transform sample from Tracking Space B.
