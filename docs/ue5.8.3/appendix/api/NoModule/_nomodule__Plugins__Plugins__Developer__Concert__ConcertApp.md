# NoModule / _nomodule__Plugins__Plugins__Developer__Concert__ConcertApp

- module root: `.`
- headers: 2; symbols: 7
- symbol kinds: class=2, member=3, prototype=2

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplication/Public/MultiUserPropertyReplicationSelection.h` (Other)


#### class `UMultiUserPropertyReplicationSelection`  
`class UMultiUserPropertyReplicationSelection : public UObject`  
_L16-23_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Holds the objects and properties to be replicated. Separate from UMultiUserReplicationStreamAsset so editor UI code editing it can be easily exist independently from UMultiUserReplicationStreamAsset.
- L22 _public member_ `FConcertObjectReplicationMap ReplicationMap;` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplication/Public/MultiUserReplicationStreamAsset.h` (Other)


#### class `UMultiUserReplicationStreamAsset`  
`class UMultiUserReplicationStreamAsset : public UObject`  
_L13-29_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Asset describing a stream of replicated data the client sends to the server.
- L20 _public member_ `FGuid StreamId;` — `UPROPERTY()` — Unique ID for this stream. CDO has value 0 to not cause issues with delta serialization.
- L23 _public member_ `TObjectPtr<UMultiUserPropertyReplicationSelection> ReplicationList;` — `UPROPERTY(Instanced)`
- L25 _public prototype_ `UMultiUserReplicationStreamAsset();`
- L28 _public prototype_ `FReplicationStreamDescription GenerateDescription() const;` — Generates a stream description based on this asset for sending to MU server.
