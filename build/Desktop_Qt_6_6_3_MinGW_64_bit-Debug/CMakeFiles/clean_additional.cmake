# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\OpenGLDonusum_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\OpenGLDonusum_autogen.dir\\ParseCache.txt"
  "OpenGLDonusum_autogen"
  )
endif()
