# Plugins / DataLinkDataTable

- module root: `Plugins/VirtualProduction/DataLink/Source/DataLinkDataTable`
- headers: 1; symbols: 6
- symbol kinds: class=1, namespace=2, prototype=2, variable=1
- PublicDependencyModuleNames: Core, CoreUObject, DataLink, Engine

### `Plugins/VirtualProduction/DataLink/Source/DataLinkDataTable/Public/DataLinkDataTableSource.h` (Public)


#### class `UDataLinkDataTableSource`  
`class UDataLinkDataTableSource : public UDataLinkNode`  
_L15-24_
- reflection: `UCLASS(MinimalAPI, Category="Data Table", DisplayName="Data Table")`
- inherits: `UDataLinkNode`
- L21 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L22 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DataLinkDataTable` (scope `UE`)
- L11 _variable_ `const FLazyName InputRow(TEXT("Inpu` (scope `UE::DataLinkDataTable`)
