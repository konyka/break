# Plugins / NeuralMorphModel

- module root: `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModel`
- headers: 6; symbols: 189
- symbol kinds: class=8, enum=2, enumerator=5, function=26, macro=4, member=63, namespace=2, prototype=76, struct=3
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ComputeFramework, CoreUObject, Engine, GeometryCache, MLDeformerFramework, NNE, NNERuntimeBasicCpu, OptimusCore, Projects, RHI, RenderCore
- PublicDependencyModuleNames: Core

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModel/Public/NeuralMorphInputInfo.h` (Public)


#### class `UNeuralMorphInputInfo`  
`class UNeuralMorphInputInfo : public UMLDeformerMorphModelInputInfo`  
_L16-103_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerMorphModelInputInfo`
- desc: The neural morph model's input info that contains all the data about the inputs to the network.
- L23 _public prototype_ `virtual void Reset() override;` — FMLDeformerInputInfo overrides.
- L31 _public prototype_ `TArray<FNeuralMorphBoneGroup>& GetBoneGroups();` — Get the bone groups. Bone groups are groups of bones that generate morph targets all together as a group rather than one for each bone individually. @return A reference to the bone groups array.
- L32 _public prototype_ `const TArray<FNeuralMorphBoneGroup>& GetBoneGroups() const;`
- L39 _public prototype_ `TArray<FNeuralMorphCurveGroup>& GetCurveGroups();` — Get the curve groups. Curve groups are groups of bones that generate morph targets all together as a group rather than one for each curve individually. @return A reference to the curve groups array.
- L40 _public prototype_ `const TArray<FNeuralMorphCurveGroup>& GetCurveGroups() const;`
- L48 _public prototype_ `int32 CalcMaxNumGroupItems() const;` — Calculate the maximum number of group items. This will look in both the bone and curve groups. So for example, if there is a curve group with 5 items, while other groups have only 2 or 3 items, this method will return 5. @return The maximum item count of all groups.
- L62 _public prototype_ `void GenerateBoneGroupIndices(TArray<int32>& OutBoneGroupIndices);` — Generate a list of index values that point inside the bone array. So the values that are output are either bone or curve numbers. The number indexes inside the array returned by GetBoneNames(). The indices are a continuous array, with each padded group concatenated. If we have two groups, like: ['UpperArm_L', 'Clavicle_L', 'Spine3'], ['UpperArm_R', 'Clavicle_R'] then this method will output something like: [10, 11, 8, 15, 16, 16]. Where each number is the index inside our bone list. As you can see there is one value (number 16) that is repeated. This is because for every group we will output the same number of items. We find the maximum group item count, using CalcMaxGroupItems() and output number of values for each group. We simply repeat the last number one or more times if we have to pad the item count of that group. This is why the number 16 is repeated two times. @param OutBoneGroupIndices The array we will fill with the right bone indices. It will automatically resize internally.
- L70 _public prototype_ `void GenerateCurveGroupIndices(TArray<int32>& OutCurveGroupIndices);` — Generates the list of index values that point inside the curve array. For more information please look at the GenerateBoneGroupIndices documentation. @param OutCurveGroupIndices The array we will fill with the right curve indices. It will automatically resize internally. @see GenerateBoneGroupIndices.
- L78 _public prototype_ `bool HasInvalidGroups() const;` — Check whether we have invalid groups or not. A group is considered invalid when it is empty, has items with the name 'None', or invalid names, or when the items (bones or curve names) do not exist in the bone or curve list. @return Returns true when there are invalid bone or curve groups, otherwise false is returned.
- L84 _public prototype_ `EMLDeformerSkinningMode GetSkinningMode() const;` — Get the skinning mode that we trained with. @return Returns the skinning mode, such as linear skinned or dual quaternion skinned.
- L89 _public prototype_ `void SetSkinningMode(EMLDeformerSkinningMode Mode);` — Set the skinning mode that was used to train with.
- L94 _protected member_ `TArray<FNeuralMorphBoneGroup> BoneGroups;` — `UPROPERTY()` — The groups of bones that generate morph targets together.
- L98 _protected member_ `TArray<FNeuralMorphCurveGroup> CurveGroups;` — `UPROPERTY()` — The groups of curves that generate morph targets together.
- L102 _protected member_ `EMLDeformerSkinningMode SkinningMode = EMLDeformerSkinningMode::Linear;` — `UPROPERTY()` — The skinning mode that was trained for.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API NEURALMORPHMODEL_API`

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModel/Public/NeuralMorphModel.h` (Public)


#### class `UNeuralMorphModel`  
`class UNeuralMorphModel : public UMLDeformerMorphModel`  
_L36-240_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerMorphModel`
- desc: The neural morph model. This generates a set of highly compressed morph targets to approximate a target deformation based on bone rotations and/or curve inputs. During inference, the neural network inside this model runs on the CPU and outputs the morph target weights for the morph targets it generated during training. Groups of bones and curves can also be defined. Those groups will generate a set of morph targets together as well. This can help when shapes depend on multiple inputs. An external morph target set is generated during training and serialized inside the ML Deformer asset that contains this model. When the ML Deformer component initializes the morph target set is registered. Most of the heavy lifting is done by the UMLDeformerMorphModel class. The neural morph model has two modes: local and global. See the ENeuralMorphMode for a description of the two. @see ENeuralMorphMode
- L42 _public prototype_ `UNeuralMorphModel(const FObjectInitializer& ObjectInitializer);`
- L45 _public prototype_ `virtual void Serialize(FArchive& Archive) override;` — UObject overrides.
- L46 _public prototype_ `virtual void PostLoad() override;`
- L47 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L51 _public function_ `virtual FString GetDisplayName() const override` — UMLDeformerModel overrides.
- L52 _public prototype_ `virtual UMLDeformerModelInstance* CreateModelInstance(UMLDeformerComponent* Component) override;`
- L53 _public prototype_ `virtual UMLDeformerInputInfo* CreateInputInfo() override;`
- L54 _public prototype_ `virtual int32 GetNumFloatsPerCurve() const override;`
- L55 _public prototype_ `virtual bool IsTrained() const override;`
- L63 _public function_ `virtual bool SupportsGlobalModeOnly() const` — Check if only global mode should be supported or not. Models that inherit from this model can disable this if they only want the global mode. This will automatically hide the UI elements related to the mode.
- L65 _public function_ `const TArray<FNeuralMorphBoneGroup>& GetBoneGroups() const`
- L66 _public function_ `const TArray<FNeuralMorphCurveGroup>& GetCurveGroups() const`
- L67 _public function_ `UNeuralMorphNetwork* GetNeuralMorphNetwork() const`
- L68 _public function_ `ENeuralMorphMode GetModelMode() const`
- L69 _public function_ `int32 GetLocalNumMorphsPerBone() const`
- L70 _public function_ `int32 GetLocalNumHiddenLayers() const`
- L71 _public function_ `int32 GetLocalNumNeuronsPerLayer() const`
- L72 _public function_ `int32 GetGlobalNumMorphs() const`
- L73 _public function_ `int32 GetGlobalNumHiddenLayers() const`
- L74 _public function_ `int32 GetGlobalNumNeuronsPerLayer() const`
- L75 _public function_ `int32 GetNumIterations() const`
- L76 _public function_ `int32 GetBatchSize() const`
- L77 _public function_ `int32 GetLocalNumMorphsPerBoneOrCurve() const`
- L78 _public function_ `float GetLearningRate() const`
- L79 _public function_ `float GetSmoothLossBeta() const`
- L80 _public function_ `float GetRegularizationFactor() const`
- L81 _public function_ `bool IsBoneMaskingEnabled() const`
- L83 _public function_ `EMLDeformerSkinningMode GetSkinningMode() const`
- L84 _public function_ `void SetSkinningMode(EMLDeformerSkinningMode SkinMode)`
- L86 _public prototype_ `void UpdateMissingGroupNames();`
- L87 _public prototype_ `void SetNeuralMorphNetwork(UNeuralMorphNetwork* Net);`
- L88 _public function_ `void SetNumIterations(int32 InNumIterations)`
- L90 _public function_ `static FName GetModePropertyName()`
- L91 _public function_ `static FName GetSkinningModePropertyName()`
- L100 _public member_ `TArray<FNeuralMorphBoneGroup> BoneGroups;` — `UPROPERTY()` — The set of bones that are grouped together and generate morph targets together as a whole. This can be used in case multiple bones are correlated to each other and work together to produce given shapes. Groups are only used when the model is in Local mode.
- L108 _public member_ `TArray<FNeuralMorphCurveGroup> CurveGroups;` — `UPROPERTY()` — The set of curves that are grouped together and generate morph targets together as a whole. This can be used in case multiple curves are correlated to each other and work together to produce given shapes. Groups are only used when the model is in Local mode.
- L113 _public member_ `TMap<FName, FNeuralMorphMaskInfo> BoneMaskInfos_DEPRECATED;` — `UE_DEPRECATED(5.5, "This property has been deprecated, please use BoneMaskInfoMap instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been deprecated, please use BoneMaskInfoMap instead."))`
- L117 _public member_ `TMap<FName, FNeuralMorphMaskInfo> BoneGroupMaskInfos_DEPRECATED;` — `UE_DEPRECATED(5.5, "This property has been deprecated, please use BoneGroupMaskInfoMap instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been deprecated, please use BoneGroupMaskInfoMap instead."))`
- L127 _public member_ `TMap<FName, FMLDeformerMaskInfo> BoneMaskInfoMap;` — `UPROPERTY()` — Information needed to generate a mask for each bone. Each mask info object contains a list of bones who's skinning influence regions should be included in the final mask for the specific bone. This information (and bone masking in general) is used inside the ENeuralMorphMode::Local mode. The FName map key represents the bone name.
- L136 _public member_ `TMap<FName, FMLDeformerMaskInfo> BoneGroupMaskInfoMap;` — `UPROPERTY()` — Information needed to generate a mask for each bone group. So the size of the array is NumGroupsInInputInfo. Each mask info object contains a list of bones who's skinning influence regions should be included in the final mask for the specific bone. This information (and bone masking in general) is used inside the ENeuralMorphMode::Local mode.
- L144 _public member_ `ENeuralMorphMode Mode = ENeuralMorphMode::Local;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings")` — The mode that the neural network will operate in. Local mode means there is one tiny network per bone, while global mode has one network for all bones together. The advantage of local mode is that it has higher performance, while global mode might result in better deformations.
- L151 _public member_ `int32 LocalNumMorphTargetsPerBone = 6;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Num Morphs Per Bone/Curve/Group", Category = "Training Settings", meta = (ClampMin = "1", ClampMax = "1000"))` — The number of morph targets to generate per bone, curve or group. Higher numbers result in better approximation of the target deformation, but also result in a higher memory footprint and slower performance.
- L158 _public member_ `int32 GlobalNumMorphTargets = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Num Morph Targets", Category = "Training Settings", meta = (ClampMin = "1", ClampMax = "1000"))` — The number of morph targets to generate in total. Higher numbers result in better approximation of the target deformation, but also result in a higher memory footprint and slower performance.
- L167 _public member_ `int32 NumIterations = 5000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", meta = (ClampMin = "1", ClampMax = "1000000"))` — The number of iterations to train the model for. If you are quickly iterating then around 1000 to 3000 iterations should be enough. If you want to generate final assets you might want to use a higher number of iterations, like 10k to 100k or even up to one million. Once the loss doesn't go down anymore, you know that more iterations most likely won't help much.
- L175 _public member_ `int32 LocalNumHiddenLayers = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, DisplayName = "Num Hidden Layers", Category = "Training Settings", meta = (ClampMin = "0", ClampMax = "5"))` — The number of hidden layers that the neural network model will have. Higher numbers will slow down performance but can deal with more complex deformations. For the local model you most likely want to stick with a value of one or two.
- L183 _public member_ `int32 LocalNumNeuronsPerLayer = 6;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, DisplayName = "Num Neurons Per Layer", Category = "Training Settings", meta = (ClampMin = "1", ClampMax = "4096"))` — The number of units/neurons per hidden layer. Higher numbers will slow down performance but allow for more complex mesh deformations. For the local mode you probably want to keep this around the same value as the number of morph targets per bone.
- L187 _public member_ `int32 GlobalNumHiddenLayers = 2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, DisplayName = "Num Hidden Layers", Category = "Training Settings", meta = (ClampMin = "0", ClampMax = "6"))` — The number of hidden layers that the neural network model will have.\nHigher numbers will slow down performance but can deal with more complex deformations.
- L191 _public member_ `int32 GlobalNumNeuronsPerLayer = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, DisplayName = "Num Neurons Per Layer", Category = "Training Settings", meta = (ClampMin = "1", ClampMax = "4096"))` — The number of units/neurons per hidden layer. Higher numbers will slow down performance but allow for more complex mesh deformations.
- L195 _public member_ `int32 BatchSize = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Training Settings", meta = (ClampMin = "1"))` — The number of frames per batch when training the model.
- L199 _public member_ `float LearningRate = 0.001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Training Settings", meta = (ClampMin = "0.000001", ClampMax = "1.0"))` — The learning rate used during the model training.
- L206 _public member_ `float RegularizationFactor = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Training Settings", meta = (ClampMin = "0.0", ClampMax = "10.0"))` — The regularization factor. Higher values can help generate more sparse morph targets, but can also lead to visual artifacts. A value of 0 disables the regularization, and gives the highest quality, at the cost of higher runtime memory usage.
- L215 _public member_ `bool bEnableBoneMasks = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Training Settings", meta = (EditCondition = "Mode == ENeuralMorphMode::Local", EditConditionHides))` — Enable the use of per bone and bone group masks. When enabled, an influence mask is generated per bone based on skinning info. This will enforce deformations localized to the area around the joint. The benefit of enabling this can be reduced GPU memory footprint, faster GPU performance and more localized deformations. If deformations do not happen near the joint then this enabling this setting can lead to those deformations possibly not being captured.
- L224 _public member_ `float SmoothLossBeta = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Training Settings", meta = (ClampMin = "0.0", ClampMax = "10.0"))` — The beta parameter in the smooth L1 loss function, which describes below which absolute error to use a squared term. If the error is above or equal to this beta value, it will use the L1 loss. This is a non-negative value, where 0 makes it behave exactly the same as an L1 loss. The value entered represents how many cm of error to allow before an L1 loss is used. Typically higher values give smoother results. If you see some noise in the trained results, even with large amount of samples and iterations, try increasing this value.
- L232 _public member_ `EMLDeformerSkinningMode SkinningMode = EMLDeformerSkinningMode::Linear;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Training Settings")` — The base skinning mode to use. The learned deltas will be applied on top of this basis. Please keep in mind that you use the same type of skinning on your character, otherwise the applied deltas are wrong. If you train using Dual Quaternions you should also run a Dual Quaternion skinning deformer before applying the ML Deltas on top.
- L239 _public member_ `TObjectPtr<UNeuralMorphNetwork> NeuralMorphNetwork;` — `UPROPERTY()` — The neural morph model network. This is a specialized network used for inference, for performance reasons.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NEURALMORPHMODEL_API`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNeuralMorphModel, Log, All);` — Declare our log category.

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModel/Public/NeuralMorphModelInstance.h` (Public)


#### class `UNeuralMorphModelInstance`  
`class UNeuralMorphModelInstance : public UMLDeformerMorphModelInstance`  
_L14-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerMorphModelInstance`
- L21 _public prototype_ `virtual void Init(USkeletalMeshComponent* SkelMeshComponent) override;` — UMLDeformerModelInstance overrides.
- L22 _public prototype_ `virtual int64 SetCurveValues(float* OutputBuffer, int64 OutputBufferSize, int64 StartIndex) override;`
- L23 _public prototype_ `virtual bool SetupInputs() override;`
- L24 _public prototype_ `virtual void Execute(float ModelWeight) override;`
- L27 _public function_ `UNeuralMorphNetworkInstance* GetNetworkInstance() const`
- L33 _protected prototype_ `void FillNetworkInputs();` — Set the network inputs.
- L37 _protected member_ `TObjectPtr<UNeuralMorphNetworkInstance> NetworkInstance;` — `UPROPERTY(Transient)`
- L39 _protected member_ `TArray<int32> BoneGroupIndices;`
- L40 _protected member_ `TArray<int32> CurveGroupIndices;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API NEURALMORPHMODEL_API`

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModel/Public/NeuralMorphModelVizSettings.h` (Public)


#### class `UNeuralMorphModelVizSettings`  
`class UNeuralMorphModelVizSettings : public UMLDeformerMorphModelVizSettings`  
_L17-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerMorphModelVizSettings`
- desc: The visualization settings specific to this model. Even if we have no new properties compared to the morph model, we still need to create this class in order to properly register a detail customization for it in our editor module.
- L24 _public function_ `bool ShouldShowMaskVizMode() const` — `UFUNCTION()`
- L37 _public member_ `ENeuralMorphMaskVizMode MaskVizMode = ENeuralMorphMaskVizMode::WhenInFocus;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", meta = (EditCondition = "ShouldShowMaskVizMode()", EditConditionHides))` — The visualization mode for the masks. Each bone, curve, bone group or curve group has a specific mask area on the mesh. This mask defines areas where generated morph targets can be active. They can be used to filter out deformations in undesired areas. For example if you rotate the left arm, you don't want the right arm to deform. The mask for the left arm can be setup in a way that it only includes vertices around the area of the left arm to enforce this.

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModel/Public/NeuralMorphNetwork.h` (Public)


#### class `UNeuralMorphMLPLayer`  
`class UE_DEPRECATED(5.4, "Neural Morph MLP no longer used for inference.") UNeuralMorphMLPLayer : public UObject`  
_L22-43_
- reflection: `UCLASS()`
- inherits: `UObject`
- L30 _public member_ `int32 NumInputs = 0;` — `UPROPERTY()`
- L33 _public member_ `int32 NumOutputs = 0;` — `UPROPERTY()`
- L36 _public member_ `int32 Depth = 1;` — `UPROPERTY()`
- L39 _public member_ `TArray<float> Weights;` — `UPROPERTY()`
- L42 _public member_ `TArray<float> Biases;` — `UPROPERTY()`

#### class `UNeuralMorphMLP`  
`class UE_DEPRECATED(5.4, "Neural Morph MLP longer used for inference.") UNeuralMorphMLP : public UObject`  
_L47-76_
- reflection: `UCLASS()`
- inherits: `UObject`
- L56 _public prototype_ `void Empty();`
- L57 _public prototype_ `bool IsEmpty() const;`
- L58 _public prototype_ `bool Load(FArchive& FileReader);`
- L59 _public prototype_ `int32 GetNumInputs() const;`
- L60 _public prototype_ `int32 GetNumOutputs() const;`
- L61 _public prototype_ `int32 GetNumLayers() const;`
- L62 _public prototype_ `UNeuralMorphMLPLayer& GetLayer(int32 Index) const;`
- L63 _public prototype_ `int32 GetMaxNumLayerInputs() const;`
- L64 _public prototype_ `int32 GetMaxNumLayerOutputs() const;`
- L68 _private prototype_ `UNeuralMorphMLPLayer* LoadNetworkLayer(FArchive& Archive);`
- L73 _private member_ `TArray<TObjectPtr<UNeuralMorphMLPLayer>> Layers;` — `UPROPERTY()`

#### class `UNeuralMorphNetwork`  
`class UNeuralMorphNetwork : public UObject`  
_L86-307_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The specialized neural network for the Neural Morph Model. This class is used to do inference at runtime at a higher performance than using UNeuralNetwork. The reason why it is faster is because it is a highly specialized network for this specific model. When the model is a local mode based model, there can be actually two neural networks inside this: one main network and a bone/curve group network. The group network uses groups of bones or curves to generate morph targets, rather than individual bones/curves.
- L94 _public prototype_ `UNeuralMorphNetwork();` — These are required because of the use of TSharedPtr
- L95 _public prototype_ `UNeuralMorphNetwork(const FObjectInitializer& ObjectInitializer);`
- L96 _public prototype_ `UNeuralMorphNetwork(FVTableHelper& Helper);`
- L97 _public prototype_ `virtual ~UNeuralMorphNetwork();`
- L100 _public prototype_ `virtual void PostLoad() override;` — Used to convert the legacy neural network format to the NNE format
- L103 _public prototype_ `void Empty();` — Clear the network, getting rid of all weights and biases.
- L111 _public prototype_ `bool IsEmpty() const;` — Check if the network is empty or not. If it is empty, it means it hasn't been loaded, and cannot do anything. Empty means it has no inputs, outputs or weights. @return Returns true if empty, otherwise false is returned.
- L119 _public prototype_ `bool Load(const FString& Filename);` — Load the network from a file on disk. When loading fails, the network will be emptied. @param Filename The file path to load from. @return Returns true when successfully loaded this model, otherwise false is returned.
- L125 _public prototype_ `UNeuralMorphNetworkInstance* CreateInstance();` — Create an instance of this neural network. @return A pointer to the neural network instance.
- L131 _public prototype_ `int32 GetNumMainInputs() const;` — Get the number of network inputs for the main network. @return The number of inputs.
- L137 _public prototype_ `int32 GetNumMainOutputs() const;` — Get the number of network outputs for the main network. @return The number of outputs.
- L143 _public prototype_ `int32 GetNumGroupInputs() const;` — Get the number of network inputs for the group network. @return The number of inputs.
- L149 _public prototype_ `int32 GetNumGroupOutputs() const;` — Get the number of network outputs for the group network. @return The number of outputs.
- L156 _public prototype_ `int32 GetNumInputs() const;` — Get the number of network inputs. This is the number of main network inputs. @return The number of inputs.
- L163 _public prototype_ `int32 GetNumOutputs() const;` — Get the number of network outputs. This is the sum of the number of main network outputs and group network outputs. @return The number of outputs.
- L169 _public prototype_ `int32 GetNumBones() const;` — Get the number of bones that are input to the network. @return The number of bones.
- L175 _public prototype_ `int32 GetNumCurves() const;` — Get the number of curves that are input to the network. @return The number of curves.
- L182 _public prototype_ `int32 GetNumMorphsPerBone() const;` — Get the number of morph targets per bone. This will only be valid if the GetMode() method returns the local model mode. For global mode networks, this will return 0. @return The number of morph targets per bone.
- L190 _public prototype_ `int32 GetNumGroups() const;` — Get the number of groups. A group is a collection of bones or curves that together generate a number of morph targets. Each group must have the same number of items. @result The number of groups.
- L198 _public prototype_ `int32 GetNumItemsPerGroup() const;` — Get the number of items per group. This indicates how many bones or curves each group has. Every group must have the same number of items. @return The number of items per group.
- L204 _public prototype_ `ENeuralMorphMode GetMode() const;` — Get the mode that the model was trained for, either global or local mode. @return The mode the model was trained for.
- L210 _public prototype_ `const TArrayView<const float> GetInputMeans() const;` — Get the means of each input, used for normalizing the input values. @return The array of mean values, one value for each network input.
- L216 _public prototype_ `const TArrayView<const float> GetInputStds() const;` — Get the standard deviations of each input, used for normalizing the input values. @return The array that contains the standard deviations, one value for each network input.
- L222 _public prototype_ `int32 GetNumFloatsPerCurve() const;` — Get the number of floats used to represent a single curve value. @return The number of float values per curve.
- L230 _public prototype_ `UE::NNE::IModelCPU* GetMainModel() const;` — Get the main Model. This is the Model (or actually a Multi-Model) that contains a small network for every bone or curve. Each small network will output a set of morph target weights. @return A pointer to the main Model.
- L238 _public prototype_ `UE::NNE::IModelCPU* GetGroupModel() const;` — Get the Model used for group of bones and curves. This Model (or actually a Multi-Model) contains small networks for the bone or curve groups. Each group will generate a set of morph target weights. @return A pointer to the Model used for the bone and curve groups.
- L246 _private member_ `TObjectPtr<UNeuralMorphMLP> MainMLP_DEPRECATED;` — `UE_DEPRECATED(5.4, "MLP Object no longer available. Please use MainModel instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Network format changed. Please use MainModel instead."))`
- L250 _private member_ `TObjectPtr<UNeuralMorphMLP> GroupMLP_DEPRECATED;` — `UE_DEPRECATED(5.4, "MLP Object no longer available. Please use GroupModel instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Network format changed. Please use GroupModel instead."))`
- L256 _private member_ `TObjectPtr<UNNEModelData> MainModelData;` — `UPROPERTY()` — The Model Data for the Main Network
- L259 _private member_ `TSharedPtr<UE::NNE::IModelCPU> MainModel;` — The Neural Network that acts as main network.
- L263 _private member_ `TObjectPtr<UNNEModelData> GroupModelData;` — `UPROPERTY()` — The Model Data for the Group Network
- L266 _private member_ `TSharedPtr<UE::NNE::IModelCPU> GroupModel;` — The Neural Network for the bone and curve groups, when in local mode.
- L270 _private member_ `TArray<float> InputMeans;` — `UPROPERTY()` — The means of the input values, used to normalize inputs.
- L274 _private member_ `TArray<float> InputStd;` — `UPROPERTY()` — The standard deviation of the input values, used to normalize inputs.
- L278 _private member_ `ENeuralMorphMode Mode = ENeuralMorphMode::Global;` — `UPROPERTY()` — The mode of the network, either local or global.
- L282 _private member_ `int32 NumMorphs = 0;` — `UPROPERTY()` — The total number of morph targets, if set Mode == Global, otherwise ignored.
- L286 _private member_ `int32 NumMorphsPerBone = 0;` — `UPROPERTY()` — The number of morph targets per bone, if set Mode == Local, otherwise ignored.
- L290 _private member_ `int32 NumBones = 0;` — `UPROPERTY()` — The number of bones that were input.
- L294 _private member_ `int32 NumCurves = 0;` — `UPROPERTY()` — The number of curves that were input.
- L298 _private member_ `int32 NumFloatsPerCurve = 1;` — `UPROPERTY()` — The number of floats per curve.
- L302 _private member_ `int32 NumGroups = 0;` — `UPROPERTY()` — The number of groups. This is a group of bones/curves that create their own morphs.
- L306 _private member_ `int32 NumItemsPerGroup = 0;` — `UPROPERTY()` — The number of items (bones/curves) per group.

#### class `UNeuralMorphNetworkInstance`  
`class UNeuralMorphNetworkInstance : public UObject`  
_L315-392_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: An instance of a UNeuralMorphNetwork. The instance holds its own input and output buffers and only reads from the network object it was instanced from. This allows it to be multithreaded.
- L325 _public prototype_ `UNeuralMorphNetworkInstance();` — These are required because of the use of TSharedPtr
- L326 _public prototype_ `UNeuralMorphNetworkInstance(const FObjectInitializer& ObjectInitializer);`
- L327 _public prototype_ `UNeuralMorphNetworkInstance(FVTableHelper& Helper);`
- L328 _public prototype_ `virtual ~UNeuralMorphNetworkInstance();`
- L334 _public prototype_ `TArrayView<float> GetInputs();` — Get the network input buffer. @return The array view of floats that represents the main network inputs.
- L335 _public prototype_ `TArrayView<const float> GetInputs() const;`
- L341 _public prototype_ `TArrayView<float> GetGroupInputs();` — Get the inputs for the group MLP. @return The array view of floats that represent the group network inputs.
- L342 _public prototype_ `TArrayView<const float> GetGroupInputs() const;`
- L348 _public prototype_ `TArrayView<float> GetOutputs();` — Get the network output buffer. @return The array view of floats that represents the network outputs.
- L349 _public prototype_ `TArrayView<const float> GetOutputs() const;`
- L355 _public prototype_ `const UNeuralMorphNetwork& GetNeuralNetwork() const;` — Get the neural network this is an instance of. @return A reference to the neural network.
- L362 _public prototype_ `void Run();` — Run the neural network, performing inference. This will update the values in the output buffer that you can get with the GetOutputs method. This also assumes you have set all the right input values already.
- L371 _private prototype_ `void Init(UNeuralMorphNetwork* InNeuralNetwork);` — Initialize this instance using a given network object. This is automatically called by the UNeuralMorphNetwork::CreateInstance() method. @param InNeuralNetwork The network that this is an instance of.
- L375 _private member_ `TArray<float> Inputs;` — The input values for the main network.
- L378 _private member_ `TArray<float> GroupInputs;` — The input values for the group network.
- L381 _private member_ `TArray<float> Outputs;` — The output values.
- L384 _private member_ `TSharedPtr<UE::NNE::IModelInstanceCPU> MainInstance;` — The inference instance data for the main Neural Network
- L387 _private member_ `TSharedPtr<UE::NNE::IModelInstanceCPU> GroupInstance;` — The inference instance data for the group Neural Network
- L391 _private member_ `TObjectPtr<UNeuralMorphNetwork> Network;` — `UPROPERTY(Transient)` — The neural network this is an instance of.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NEURALMORPHMODEL_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNE` (scope `UE`)

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModel/Public/NeuralMorphTypes.h` (Public)


#### enum `ENeuralMorphMode`  
`enum class ENeuralMorphMode : uint8`  
_L19-35_
- reflection: `UENUM()`
- desc: The mode of the model, either local or global. In local mode the network contains a super simple neural network for each bone, while in global mode all bones and curves are input to one larger fully connected network. The local mode has faster performance, while global mode can result in higher quality deformation. This model runs its neural network on the CPU, but uses comrpessed GPU based morph targets, which require shader model 5.
- L26 _public enumerator_ `Local` — Each bone creates a set of morph targets and has its own small neural network. The local mode can also create more localized morph targets and tends to use slightly less memory. This mode is faster to process on the CPU side.
- L34 _public enumerator_ `Global` — There is one fully connected neural network that generates a set of morph targets. This has a slightly higher CPU overhead, but could result in higher quality. The Global mode is basically the same as the Vertex Delta Model, but runs the neural network on the CPU and uses GPU compressed morph targets.

#### enum `ENeuralMorphMaskVizMode`  
`enum class ENeuralMorphMaskVizMode : uint8`  
_L45-55_
- reflection: `UENUM()`
- desc: The visualization mode for the masks. Each bone, curve, bone group or curve group has a specific mask area on the mesh. This mask defines areas where generated morph targets can be active. They can be used to filter out deformations in undesired areas. For example if you rotate the left arm, you don't want the right arm to deform. The mask for the left arm can be setup in a way that it only includes vertices around the area of the left arm to enforce this.
- L48 _public enumerator_ `Off` — Do not display the masks in the viewport.
- L51 _public enumerator_ `WhenInFocus` — Only show the masks inside the viewport when the inputs widget on the right side of the UI is in focus. Show the mask for the selected item (bone, curve, bone group, curve group).
- L54 _public enumerator_ `Always` — Always show the selected mask. The mask selected is defined by what is selected in the input widget on the right side of the UI.

#### struct `FNeuralMorphBoneGroup`  
`struct FNeuralMorphBoneGroup`  
_L62-74_
- reflection: `USTRUCT()`
- desc: A group of bones, which can generate morph targets together. This is useful when there are specific correlations between different bones, that all effect the same region on the body.
- L69 _public member_ `FName GroupName;` — `UPROPERTY()` — The name of the group, also shown in the UI.
- L73 _public member_ `TArray<FBoneReference> BoneNames;` — `UPROPERTY(EditAnywhere, Category = "Bones")` — The list of bones that should form a group together.

#### struct `FNeuralMorphCurveGroup`  
`struct FNeuralMorphCurveGroup`  
_L81-93_
- reflection: `USTRUCT()`
- desc: A group of curves, which can generate morph targets together. This is useful when there are specific correlations between different curves, that all effect the same region on the body.
- L88 _public member_ `FName GroupName;` — `UPROPERTY()` — The name of the group, also shown in the UI.
- L92 _public member_ `TArray<FMLDeformerCurveReference> CurveNames;` — `UPROPERTY(EditAnywhere, Category = "Curves")` — The list of curves that should form a group together.

#### struct `FNeuralMorphMaskInfo`  
`struct UE_DEPRECATED(5.5, "This class has been deprecated, please use FMLDeformerMaskInfo instead.") FNeuralMorphMaskInfo`  
_L103-119_
- reflection: `USTRUCT()`
- desc: Information needed to generate the mask for a specific bone. This includes a list of bone names. Each bone has a skinning influence mask. The final mask will be a merge of all the bone masks of bones listed inside this info struct. There will be an array of these structs, one for each bone.
- L110 _public member_ `TArray<FName> BoneNames;` — `UPROPERTY()` — The list of bone names that should be included in the mask generation.
- L114 _public member_ `EMLDeformerMaskingMode MaskMode = EMLDeformerMaskingMode::Generated;` — `UPROPERTY()` — The masking mode.
- L118 _public member_ `FName VertexAttributeName;` — `UPROPERTY()` — If the masking mode is set to VertexAttribute then we can check which attribute to use using this member.
