# Plugins / DatabaseSupport

- module root: `Plugins/Runtime/Database/DatabaseSupport/Source/DatabaseSupport`
- headers: 2; symbols: 42
- symbol kinds: class=4, enum=1, enumerator=4, function=29, member=3, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/Database/DatabaseSupport/Source/DatabaseSupport/Public/Database.h` (Public)


#### enum `EDataBaseUnrealTypes`  
`enum EDataBaseUnrealTypes`  
_L10-16_
- desc: Enums for Database types.  Each Database has their own set of DB types and
- L12 _public enumerator_ `DBT_UNKOWN`
- L13 _public enumerator_ `DBT_FLOAT`
- L14 _public enumerator_ `DBT_INT`
- L15 _public enumerator_ `DBT_STRING`

#### struct `FDatabaseColumnInfo`  
`struct FDatabaseColumnInfo`  
_L22-39_
- desc: This struct holds info relating to a column.  Specifically, we need to get back certain meta info from a RecordSet so we can "Get" data from it.
- L25 _public function_ `FDatabaseColumnInfo(): DataType(DBT_UNKOWN)` — Default constructor
- L28 _public member_ `FString ColumnName;` — The name of the column
- L31 _public member_ `EDataBaseUnrealTypes DataType;` — This is the type of data in this column.  (e.g. so you can do GetFloat or GetInt on the column
- L34 _public function_ `bool operator==(const FDatabaseColumnInfo& OtherFDatabaseColumnInfo) const`

#### class `FDataBaseRecordSet`  
`class FDataBaseRecordSet`  
_L45-202_
- desc: Empty base class for iterating over database records returned via query. Used on platforms not supporting a direct database connection.
- L51 _protected function_ `virtual void MoveToFirst()` — Moves to the first record in the set.
- L54 _protected function_ `virtual void MoveToNext()` — Moves to the next record in the set.
- L61 _protected function_ `virtual bool IsAtEnd() const` — Returns whether we are at the end. @return true if at the end, false otherwise
- L71 _public function_ `virtual bool HasError() const` — @return True if the record set has an error set.
- L78 _public function_ `virtual int32 GetErrorCode() const` — @return The raw error code that was set, if any (@see HasError).
- L85 _public function_ `virtual FString GetErrorMessage() const` — @return The error message that was set, if any (@see HasError).
- L93 _public function_ `virtual int32 GetRecordCount() const` — Returns a count of the number of records in the record set
- L103 _public function_ `virtual FString GetString( const TCHAR* Column ) const` — Returns a string associated with the passed in field/ column for the current row. @param	Column	Name of column to retrieve data for in current row
- L113 _public function_ `virtual int32 GetInt( const TCHAR* Column ) const` — Returns an integer associated with the passed in field/ column for the current row. @param	Column	Name of column to retrieve data for in current row
- L123 _public function_ `virtual float GetFloat( const TCHAR* Column ) const` — Returns a float associated with the passed in field/ column for the current row. @param	Column	Name of column to retrieve data for in current row
- L133 _public function_ `virtual int64 GetBigInt( const TCHAR* Column ) const` — Returns a int64 associated with the passed in field/ column for the current row. @param	Column	Name of column to retrieve data for in current row
- L142 _public function_ `virtual TArray<FDatabaseColumnInfo> GetColumnNames() const` — Returns the set of column names for this Recordset.  This is useful for determining what you can actually ask the record set for without having to hard code those ahead of time.
- L149 _public function_ `virtual ~FDataBaseRecordSet()` — Virtual destructor as class has virtual functions.

#### class `FDataBaseRecordSet::TIterator`  
`class TIterator`  
_L155-201_
- desc: Iterator helper class based on FObjectIterator.
- L163 _public function_ `TIterator( FDataBaseRecordSet* InRecordSet ) : RecordSet( InRecordSet )` — Initialization constructor. @param	InRecordSet		RecordSet to iterate over
- L172 _public function_ `void operator++()` — operator++ used to iterate to next element.
- L178 _public function_ `inline explicit operator bool() const` — Conversion to "bool" returning true if the iterator is valid.
- L183 _public function_ `inline bool operator !() const` — inverse of the "bool" operator
- L189 _public function_ `inline FDataBaseRecordSet* operator*() const` — Access operators
- L193 _public function_ `inline FDataBaseRecordSet* operator->() const`
- L200 _protected member_ `FDataBaseRecordSet* RecordSet;` — Database record set being iterated over.

#### class `FDataBaseConnection`  
`class FDataBaseConnection`  
_L208-278_
- desc: Empty base class for database access via executing SQL commands. Used on platforms not supporting a direct database connection.
- L212 _public function_ `virtual ~FDataBaseConnection()` — Virtual destructor as we have virtual functions.
- L224 _public function_ `virtual bool Open( const TCHAR* ConnectionString, const TCHAR* RemoteConnectionIP, const TCHAR* RemoteConnectionStringOverride )` — Opens a connection to the database. @param	ConnectionString	Connection string passed to database layer @param   RemoteConnectionIP  The IP address which the RemoteConnection should connect to @param   RemoteConnectionStringOverride  The connection string which the RemoteConnection is going to utilize @return	true if connection was successfully established, false otherwise
- L232 _public function_ `virtual void Close()` — Closes connection to database.
- L242 _public function_ `virtual bool Execute( const TCHAR* CommandString )` — Executes the passed in command on the database. @param CommandString		Command to execute @return true if execution was successful, false otherwise
- L256 _public function_ `virtual bool Execute( const TCHAR* CommandString, FDataBaseRecordSet*& RecordSet )` — Executes the passed in command on the database. The caller is responsible for deleting the created RecordSet. @param CommandString		Command to execute @param RecordSet			Reference to recordset pointer that is going to hold result @return true if execution was successful, false otherwise
- L271 _public function_ `inline bool Execute(const TCHAR* CommandString, TUniquePtr< FDataBaseRecordSet >& RecordSet)` — Executes the passed in command on the database. The caller is responsible for deleting the created RecordSet. @param CommandString		Command to execute @param RecordSet			Reference to recordset pointer that is going to hold result @return true if execution was successful, false otherwise

### `Plugins/Runtime/Database/DatabaseSupport/Source/DatabaseSupport/Public/DatabaseSupport.h` (Public)


#### class `IDatabaseSupport`  
`class IDatabaseSupport : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline IDatabaseSupport& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
