# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BTreeDS_autogen"
  "CMakeFiles\\BTreeDS_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BTreeDS_autogen.dir\\ParseCache.txt"
  )
endif()
