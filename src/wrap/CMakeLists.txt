#get current source files
if (CRI_CLIENT)
    find_program(CMD_PROTOC protoc)
    find_program(CMD_GRPC_CPP_PLUGIN grpc_cpp_plugin)
    execute_process(COMMAND ${CMD_PROTOC} -I ${CMAKE_CURRENT_SOURCE_DIR} --grpc_out=${CMAKE_CURRENT_SOURCE_DIR}
                    --plugin=protoc-gen-grpc=${CMD_GRPC_CPP_PLUGIN} ${CMAKE_CURRENT_SOURCE_DIR}/api.proto)
    execute_process(COMMAND ${CMD_PROTOC} -I ${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/api.proto)
endif()

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
