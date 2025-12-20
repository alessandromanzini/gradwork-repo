cmake_minimum_required( VERSION 4.0 )
project( "gradwork-repo" )

set( CMAKE_CXX_STANDARD 26 )

add_executable( ${PROJECT_NAME} main.cpp plf_hive.h
                profiling.h )

add_executable( ${PROJECT_NAME}-hive-test plf_hive_test_suite.cpp plf_hive.h )
