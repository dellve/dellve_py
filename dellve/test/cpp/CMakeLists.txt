################################################################################
#	Google Test Installation 
################################################################################

find_package(Threads REQUIRED)

include(ExternalProject) # enable CMake module for loading external projects

# TODO: rewrite this to use gtest git repo instead of downloading .zip file
ExternalProject_Add(gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create GTesh & GMock 
add_library(libgmock IMPORTED STATIC GLOBAL)
add_library(libgtest IMPORTED STATIC GLOBAL)

# Add gtest & GMock dependencies
add_dependencies(libgtest gtest)
add_dependencies(libgmock gtest)

# Set gtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Set GMock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# TODO: make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories(${source_dir}/googletest/include)
include_directories(${source_dir}/googlemock/include)

################################################################################
#	DELLve Tests 
################################################################################

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_subdirectory(PluginProxyTest)

# TODO: add more tests here