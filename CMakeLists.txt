project(ptcr)

cmake_minimum_required (VERSION 2.8)

add_definitions(-D_GNU_SOURCE)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "-Wall -O3")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
#install
set(install_conf_dir "/etc/ptcr/")
install(FILES configs/container_config.json
    DESTINATION ${install_conf_dir} PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE)
install(FILES configs/pod_config.json
    DESTINATION ${install_conf_dir} PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE)
install(FILES configs/ptcr.yml
    DESTINATION ${install_conf_dir} PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE)
install(FILES configs/draw.py
    DESTINATION ${install_conf_dir} PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE)

# uninstall
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
