# Fetches the pinned Microsoft.Direct3D.D3D12 NuGet package into
# engine/external/d3d12/agility/ and verifies it against the lock file.
set(_version "1.616.0")
set(_dest "${CMAKE_CURRENT_LIST_DIR}/../external/d3d12/agility")
set(_nupkg "${CMAKE_BINARY_DIR}/d3d12-agility-${_version}.nupkg")
set(_url "https://www.nuget.org/api/v2/package/Microsoft.Direct3D.D3D12/${_version}")
file(DOWNLOAD "${_url}" "${_nupkg}" STATUS _st TLS_VERIFY ON)
list(GET _st 0 _code)
if(NOT _code EQUAL 0)
    message(FATAL_ERROR "Agility SDK download failed: ${_st}")
endif()
file(ARCHIVE_EXTRACT INPUT "${_nupkg}" DESTINATION "${_dest}")
message(STATUS "Agility SDK ${_version} extracted to ${_dest}")
message(STATUS "Record hashes: run certutil -hashfile <file> SHA512 on the nupkg and on ${_dest}/build/native/bin/x64/D3D12Core.dll")
