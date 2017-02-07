
################################################################################
#	Mock Plugin 
################################################################################

add_library(PluginProxyTestPlugin MODULE "PluginProxyTestPlugin.cpp")

set_property(TARGET PluginProxyTestPlugin PROPERTY CXX_STANDARD 11)

target_include_directories(PluginProxyTestPlugin PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
    PRIVATE .)

TARGET_LINK_LIBRARIES(PluginProxyTestPlugin)

################################################################################
#	Test Executable 
################################################################################

add_executable(PluginProxyTest "PluginProxyTest.cpp")

set_property(TARGET PluginProxyTest PROPERTY CXX_STANDARD 11)

add_dependencies(PluginProxyTest PluginProxyTestPlugin)

target_link_libraries(PluginProxyTest libgtest libgmock)

add_test(NAME PluginProxyTest COMMAND PluginProxyTest)

