# Plugins / SQLiteSupport

- module root: `Plugins/Runtime/Database/SQLiteSupport/Source/SQLiteSupport`
- headers: 3; symbols: 30
- symbol kinds: class=3, function=2, member=6, prototype=19
- PublicDependencyModuleNames: Core, DatabaseSupport, SQLiteCore

### `Plugins/Runtime/Database/SQLiteSupport/Source/SQLiteSupport/Public/SQLiteDatabaseConnection.h` (Public)


#### class `FSQLiteDatabaseConnection`  
`class FSQLiteDatabaseConnection : public FDataBaseConnection`  
_L13-39_
- inherits: `FDataBaseConnection`
- desc: SQLite database file
- L17 _public prototype_ `virtual void Close();` — Closes the database handle and unlocks the file
- L20 _public prototype_ `virtual bool Execute(const TCHAR* CommandString) override;` — Execute a command on the database without storing the result set (if any)
- L23 _public prototype_ `bool Execute(const TCHAR* CommandString, FSQLiteResultSet*& RecordSet);` — Executes the command string on the currently opened database, returning a FSQLiteResultSet in RecordSet. Caller is responsible for freeing RecordSet
- L30 _public prototype_ `virtual bool Open(const TCHAR* ConnectionString, const TCHAR* RemoteConnectionIP, const TCHAR* RemoteConnectionStringOverride);` — Open a SQLite file @param	ConnectionString	Path to the file that should be opened @param	RemoteConnectionIP	Unused with this implementation @param	ConnectionString	Unused with this implementation
- L33 _public prototype_ `virtual bool Execute(const TCHAR* CommandString, FDataBaseRecordSet*& RecordSet) override;` — Overriding to address warning C4264 - SQLite databases should call Execute(const TCHAR* CommandString, FSQLiteResultSet*& RecordSet) instead
- L35 _public prototype_ `FString GetLastError();`
- L38 _protected member_ `FSQLiteDatabase Database;`

### `Plugins/Runtime/Database/SQLiteSupport/Source/SQLiteSupport/Public/SQLiteResultSet.h` (Public)


#### class `FSQLiteResultSet`  
`class FSQLiteResultSet : public FDataBaseRecordSet`  
_L12-40_
- inherits: `FDataBaseRecordSet`
- desc: Result set for SQLite database queries
- L16 _protected prototype_ `virtual void MoveToFirst() override;`
- L17 _protected prototype_ `virtual void MoveToNext() override;`
- L18 _protected prototype_ `virtual bool IsAtEnd() const override;`
- L21 _public prototype_ `virtual bool HasError() const override;`
- L22 _public prototype_ `virtual int32 GetErrorCode() const override;`
- L23 _public prototype_ `virtual FString GetErrorMessage() const override;`
- L24 _public prototype_ `virtual int32 GetRecordCount() const override;`
- L25 _public prototype_ `virtual FString GetString(const TCHAR* Column) const override;`
- L26 _public prototype_ `virtual int32 GetInt(const TCHAR* Column) const override;`
- L27 _public prototype_ `virtual float GetFloat(const TCHAR* Column) const override;`
- L28 _public prototype_ `virtual int64 GetBigInt(const TCHAR* Column) const override;`
- L29 _public prototype_ `virtual TArray<FDatabaseColumnInfo> GetColumnNames() const override;`
- L32 _public prototype_ `explicit FSQLiteResultSet(FSQLitePreparedStatement&& InPreparedStatement);`
- L35 _private member_ `FSQLitePreparedStatement PreparedStatement;`
- L36 _private member_ `TArray<FDatabaseColumnInfo> ColumnInfos;`
- L37 _private member_ `int32 NumberOfRecords = 0;`
- L38 _private member_ `int32 StepResultErrorCode = 0;`
- L39 _private member_ `ESQLitePreparedStatementStepResult StepResult = ESQLitePreparedStatementStepResult::Done;`

### `Plugins/Runtime/Database/SQLiteSupport/Source/SQLiteSupport/Public/SQLiteSupport.h` (Public)


#### class `ISQLiteSupport`  
`class ISQLiteSupport : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline ISQLiteSupport& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
