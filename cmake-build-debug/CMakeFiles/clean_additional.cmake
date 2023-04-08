# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Proyecto_1_Datos_ll_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Proyecto_1_Datos_ll_autogen.dir/ParseCache.txt"
  "Proyecto_1_Datos_ll_autogen"
  )
endif()
