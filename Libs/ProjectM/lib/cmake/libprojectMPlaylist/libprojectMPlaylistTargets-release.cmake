#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libprojectM::playlist" for configuration "Release"
set_property(TARGET libprojectM::playlist APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libprojectM::playlist PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/projectM_playlist.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/projectM_playlist.dll"
  )

list(APPEND _cmake_import_check_targets libprojectM::playlist )
list(APPEND _cmake_import_check_files_for_libprojectM::playlist "${_IMPORT_PREFIX}/lib/projectM_playlist.lib" "${_IMPORT_PREFIX}/lib/projectM_playlist.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
