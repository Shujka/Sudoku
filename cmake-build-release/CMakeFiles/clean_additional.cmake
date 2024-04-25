# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/main_variant_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/main_variant_autogen.dir/ParseCache.txt"
  "main_variant_autogen"
  )
endif()
