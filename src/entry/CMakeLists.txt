#get current source files
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} entry_src)

#enable scope
set(DIR_ENTRY_SRCS
    ${entry_src}
    PARENT_SCOPE
)
set(DIR_ENTRY_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)
