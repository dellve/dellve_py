
# Mock Plugin 

add_library(dellve_test_plugin MODULE "dellve_test_plugin.cpp")

set_property(TARGET dellve_test_plugin PROPERTY CXX_STANDARD 11)
set_property(TARGET dellve_test_plugin PROPERTY PREFIX "")
set_property(TARGET dellve_test_plugin PROPERTY SUFFIX ".dellveplugin")

target_include_directories(dellve_test_plugin PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include>
    PRIVATE .)

TARGET_LINK_LIBRARIES(dellve_test_plugin)

