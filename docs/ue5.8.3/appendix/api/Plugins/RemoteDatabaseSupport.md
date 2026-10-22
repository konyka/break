# Plugins / RemoteDatabaseSupport

- module root: `Plugins/Runtime/Database/RemoteDatabaseSupport/Source/RemoteDatabaseSupport`
- headers: 2; symbols: 23
- symbol kinds: class=3, function=2, member=3, prototype=15
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Sockets
- PublicDependencyModuleNames: Core, DatabaseSupport

### `Plugins/Runtime/Database/RemoteDatabaseSupport/Source/RemoteDatabaseSupport/Public/RemoteDatabaseConnection.h` (Public)


#### class `FRemoteDatabaseConnection`  
`class FRemoteDatabaseConnection : public FDataBaseConnection`  
_L14-72_
- inherits: `FDataBaseConnection`
- desc: This class allows for connections to a remote database proxy that allows any platform, regardless of native DB support, to talk to a DB.
- L17 _private member_ `FSocket *Socket;`
- L23 _public prototype_ `FRemoteDatabaseConnection();` — Constructor.
- L28 _public prototype_ `virtual ~FRemoteDatabaseConnection();` — Destructor.
- L39 _public prototype_ `virtual bool Open( const TCHAR* ConnectionString, const TCHAR* RemoteConnectionIP, const TCHAR* RemoteConnectionStringOverride );` — Opens a connection to the database. @param	ConnectionString	Connection string passed to database layer @param   RemoteConnectionIP  The IP address which the RemoteConnection should connect to @param   RemoteConnectionStringOverride  The connection string which the RemoteConnection is going to utilize @return	true if connection was successfully established, false otherwise
- L44 _public prototype_ `virtual void Close();` — Closes connection to database.
- L53 _public prototype_ `virtual bool Execute(const TCHAR* CommandString);` — Executes the passed in command on the database. @param CommandString		Command to execute @return true if execution was successful, false otherwise
- L64 _public prototype_ `virtual bool Execute(const TCHAR* CommandString, FDataBaseRecordSet*& RecordSet);` — Executes the passed in command on the database. The caller is responsible for deleting the created RecordSet. @param CommandString		Command to execute @param RecordSet			Reference to recordset pointer that is going to hold result @return true if execution was successful, false otherwise
- L71 _public prototype_ `bool SetConnectionString(const TCHAR* ConnectionString);` — Sets the connection string to be used for this connection in the DB proxy. @param	ConnectionString	The new connection string to use.

#### class `FRemoteDataBaseRecordSet`  
`class FRemoteDataBaseRecordSet : public FDataBaseRecordSet`  
_L77-128_
- inherits: `FDataBaseRecordSet`
- desc: A record set that is accessed from a DB proxy.
- L81 _private member_ `FString ID;` — The record set's ID within the DB proxy.
- L84 _private member_ `FSocket *Socket;` — The connection to the proxy DB
- L89 _protected prototype_ `virtual void MoveToFirst();` — Moves to the first record in the set.
- L92 _protected prototype_ `virtual void MoveToNext();` — Moves to the next record in the set.
- L99 _protected prototype_ `virtual bool IsAtEnd() const;` — Returns whether we are at the end. @return true if at the end, false otherwise
- L107 _public prototype_ `virtual FString GetString( const TCHAR* Column ) const;` — Returns a string associated with the passed in field/ column for the current row. @param	Column	Name of column to retrieve data for in current row
- L114 _public prototype_ `virtual int32 GetInt( const TCHAR* Column ) const;` — Returns an integer associated with the passed in field/ column for the current row. @param	Column	Name of column to retrieve data for in current row
- L121 _public prototype_ `virtual float GetFloat( const TCHAR* Column ) const;` — Returns a float associated with the passed in field/ column for the current row. @param	Column	Name of column to retrieve data for in current row
- L124 _public prototype_ `FRemoteDataBaseRecordSet(int32 ResultSetID, FSocket *Connection);` — Constructor.
- L127 _public prototype_ `virtual ~FRemoteDataBaseRecordSet();` — Virtual destructor as class has virtual functions.

### `Plugins/Runtime/Database/RemoteDatabaseSupport/Source/RemoteDatabaseSupport/Public/RemoteDatabaseSupport.h` (Public)


#### class `IRemoteDatabaseSupport`  
`class IRemoteDatabaseSupport : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline IRemoteDatabaseSupport& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
