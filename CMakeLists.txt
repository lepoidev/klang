cmake_minimum_required(VERSION 3.19)

if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

project(klang)
include(CTest)
include("${CMAKE_SOURCE_DIR}/cmake/create_symlink.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/find_all_k_files.cmake")

option(ENABLE_TESTING "Testing Enabled" ON)
enable_testing()
set(target klang)
set(parser klang-parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Bring in the required packages
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# set antlr4 version
set(ANTLR4_VER 4.9.1)

# set variables for antlr4 cmake files
set(ANTLR4_JAR_NAME antlr-${ANTLR4_VER}-complete.jar)
set(ANTLR_JAR_PATH ${CMAKE_SOURCE_DIR}/build)
set(ANTLR4_JAR ${ANTLR_JAR_PATH}/${ANTLR4_JAR_NAME})
include(DownloadAntlr4Jar REQUIRED)
set(ANTLR4_TAG ${ANTLR4_VER})
set(ANTLR_EXECUTABLE ${ANTLR4_JAR})

# link to anltr4 static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
# set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

set(PATH_TO_GRAMMAR ${CMAKE_CURRENT_SOURCE_DIR}/grammar/K.g4)
set(ANTLR4_CPP_GENERATED_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gen/)
set(ANTLR_NAMESPACE "K")

antlr_target(KlangParser
             ${PATH_TO_GRAMMAR}
             OUTPUT_DIRECTORY ${ANTLR4_CPP_GENERATED_SRC_DIR}
             VISITOR)

#include_directories(${ANTLR4_INCLUDE_DIRS})
#include_directories(${ANTLR4_CPP_GENERATED_SRC_DIR})

add_library(${parser} STATIC ${ANTLR_KlangParser_CXX_OUTPUTS})
#target_include_directories(${parser} PUBLIC ${ANTLR_INCLUDE_DIRS})

# create executable
add_executable(${target} main.cpp ${ANTLR4_CPP_GENERATED_SRC_DIR})
add_dependencies(${target} ${parser})
target_include_directories(${target} PUBLIC ${ANTLR4_INCLUDE_DIRS})
target_include_directories(${target} PUBLIC ${ANTLR_KlangParser_OUTPUT_DIR})
target_link_libraries(${target} antlr4_static)
create_symlink(${target} ${CMAKE_SOURCE_DIR}/bin)

# testing
enable_testing()
set(grammar_tester klang-grammar-tester)
set(TESTING_PATH ${CMAKE_SOURCE_DIR}/testing)
set(TESTING_BUILD ${TESTING_PATH}/build)
set(TESTING_BIN ${TESTING_PATH}/bin)

add_subdirectory(${TESTING_PATH} ${TESTING_BUILD})
create_symlink(${grammar_tester} ${TESTING_BIN})
