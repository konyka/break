# Developer / MeshUtilitiesEngine

- module root: `Source/Developer/MeshUtilitiesEngine`
- headers: 1; symbols: 3
- symbol kinds: class=1, macro=1, prototype=1
- PrivateDependencyModuleNames: Core, CoreUObject
- PublicDependencyModuleNames: Engine, MeshUtilitiesCommon

### `Source/Developer/MeshUtilitiesEngine/Public/MeshUtilitiesEngine.h` (Public)


#### class `FMeshUtilitiesEngine`  
`class FMeshUtilitiesEngine`  
_L12-25_
- L24 _public prototype_ `static void CalcBoneVertInfos(USkeletalMesh* SkeletalMesh, TArray<FBoneVertInfo>& Infos, bool bOnlyDominant, int32 SourceLodIndex);` — Calculate the verts associated weighted to each bone of the skeleton. The vertices returned are in the local space of the bone. @param	SkeletalMesh	The target skeletal mesh. @param	Infos			The output array of vertices associated with each bone. @param	bOnlyDominant	Controls whether a vertex is added to the info for a bone if it is most controlled by that bone, or if that bone has ANY influence on that vert. @param	SourceLodIndex	Use the specified LOD index to query the bone vert info.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MESHUTILITIESENGINE_API`
