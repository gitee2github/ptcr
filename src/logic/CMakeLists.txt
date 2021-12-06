#get current source files

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} logic_src)

#enable scope
set(DIR_LOGIC_SRCS
    ${logic_src}
    PARENT_SCOPE
)

set(DIR_LOGIC_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)
