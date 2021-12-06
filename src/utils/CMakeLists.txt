#get current source files
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} utils_src)

#enable scope
set(DIR_UTILS_SRCS
    ${utils_src}
    PARENT_SCOPE
)
set(DIR_UTILS_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)
