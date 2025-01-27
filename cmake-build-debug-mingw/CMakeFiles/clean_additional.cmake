# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "submodules\\qcustomplot-fetch\\CMakeFiles\\qcustomplot_autogen.dir\\AutogenUsed.txt"
  "submodules\\qcustomplot-fetch\\CMakeFiles\\qcustomplot_autogen.dir\\ParseCache.txt"
  "submodules\\qcustomplot-fetch\\qcustomplot_autogen"
  )
endif()
