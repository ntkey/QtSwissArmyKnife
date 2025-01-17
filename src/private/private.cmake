include(.cmake/sak_common.cmake)

file(
  GLOB dirs
  LIST_DIRECTORIES true
  "${CMAKE_SOURCE_DIR}/src/private/*")

set(SAK_HAS_PRIVATE_MODULE false)

foreach(dir ${dirs})
  if(IS_DIRECTORY ${dir})
    if(NOT ${SAK_HAS_PRIVATE_MODULE})
      set(SAK_HAS_PRIVATE_MODULE true)
    endif()
  endif()
endforeach()

if(${SAK_HAS_PRIVATE_MODULE})
  sak_add_subdiretory("nodeeditor-3.0.10")
  add_compile_definitions(SAK_IMPORT_MODULE_PRIVATE)
endif()

foreach(dir ${dirs})
  if(IS_DIRECTORY ${dir})
    file(RELATIVE_PATH cooked_dir ${CMAKE_SOURCE_DIR} ${dir})
    add_subdirectory(${cooked_dir})
  endif()
endforeach()
