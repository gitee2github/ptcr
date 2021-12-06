#get current source files
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} wrap_src)

#enable scope
set(DIR_WRAP_SRCS
    ${wrap_src}
    PARENT_SCOPE
)
set(DIR_WRAP_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)