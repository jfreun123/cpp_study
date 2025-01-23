add_library(cppstudysrc INTERFACE)
target_include_directories( cppstudysrc 
                            INTERFACE 
                            ${CMAKE_CURRENT_SOURCE_DIR}/multithreading
                            ${CMAKE_CURRENT_SOURCE_DIR}/core
)