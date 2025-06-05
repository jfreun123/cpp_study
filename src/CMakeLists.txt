add_library(cppstudysrc INTERFACE)
target_include_directories( cppstudysrc 
                            INTERFACE 
                            ${CMAKE_CURRENT_SOURCE_DIR}/core
                            ${CMAKE_CURRENT_SOURCE_DIR}/lisp_parser
                            ${CMAKE_CURRENT_SOURCE_DIR}/multithreading
                            ${CMAKE_CURRENT_SOURCE_DIR}/prime
                            ${CMAKE_CURRENT_SOURCE_DIR}/set_intersection
                            ${CMAKE_CURRENT_SOURCE_DIR}/sudoku
)