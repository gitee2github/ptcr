set(CHECK_INCLUDE_DIRS 
    {DIR_ENTRY_INCS}
    {DIR_LOGIC_INCS}
    {DIR_WRAP_INCS}
    {DIR_UTILS_INCS}
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} src_dir)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/entry)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/logic)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/wrap)

add_executable(ptcr
    ${src_dir}
    ${DIR_ENTRY_SRCS}
    ${DIR_LOGIC_SRCS}
    ${DIR_WRAP_SRCS}
    ${DIR_UTILS_SRCS}
)

target_include_directories(ptcr PUBLIC
    ${DIR_ENTRY_INCS}
    ${DIR_LOGIC_INCS}
    ${DIR_UTILS_INCS}
    ${DIR_WRAP_INCS}
)

target_link_libraries(ptcr -lyaml-cpp -lpthread)

install(TARGETS ptcr RUNTIME DESTINATION bin)
