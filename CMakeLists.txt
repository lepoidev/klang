cmake_minimum_required(VERSION 3.19)

if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

project(klang)
include(CTest)
include("${CMAKE_SOURCE_DIR}/cmake/create_symlink.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/find_all_k_files.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/add_grammar_tests_from_folder.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/add_compiled_tests_from_folder.cmake")

option(ENABLE_TESTING "Testing Enabled" ON)
enable_testing()
set(compiler klang)
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

antlr_target(KlangParser
             ${PATH_TO_GRAMMAR}
             OUTPUT_DIRECTORY ${ANTLR4_CPP_GENERATED_SRC_DIR}
             DEPENDS antlr4_static
             VISITOR)

add_library(${parser} STATIC ${ANTLR_KlangParser_CXX_OUTPUTS})

# set source vars
set(KLANG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(KLANG_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)

# generate AST headers
include(CreateASTNodesHeader REQUIRED)

# create compiler executable
add_executable(${compiler} ${ANTLR4_CPP_GENERATED_SRC_DIR})

# ANLTR
target_link_libraries(${compiler} antlr4_static)
target_link_libraries(${compiler} ${parser})
add_dependencies(${compiler} antlr4_static)
add_dependencies(${compiler} ${parser})
target_include_directories(${compiler} PUBLIC ${ANTLR4_INCLUDE_DIRS})
target_include_directories(${compiler} PUBLIC ${ANTLR_KlangParser_OUTPUT_DIR})

# LLVM
message(STATUS "Searching for LLVMConfig.cmake in ${LLVM_DIR}")
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Using LLVM ${LLVM_VERSION_MAJOR}.${LLVM_VERSION_MINOR}.${LLVM_VERSION_PATCH}")
llvm_map_components_to_libnames(llvm_libs core)
target_link_libraries(${compiler} ${llvm_libs})
target_include_directories(${compiler} PUBLIC ${LLVM_INCLUDE_DIRS})
target_compile_definitions(${compiler} PUBLIC ${LLVM_DEFINITIONS})

# klang
add_subdirectory(${KLANG_SOURCE_DIR})
target_include_directories(${compiler} PUBLIC ${KLANG_INCLUDE_DIR})

# precompiled header
target_precompile_headers(${compiler}
  PUBLIC
    <iostream>
    <memory>
    <string>
    <deque>
    <algorithm>
    <functional>
    <unordered_map>
    <unordered_set>
    <llvm/IR/Module.h>
    <llvm/IR/LLVMContext.h>
    <llvm/IR/IRBuilder.h>
    <llvm/IR/Value.h>
    <llvm/IR/Verifier.h>
    <llvm/Support/raw_os_ostream.h>
)

create_symlink(${compiler} ${CMAKE_SOURCE_DIR}/bin)

# testing
enable_testing()
set(grammar_tester klang-grammar-tester)
set(TESTING_PATH ${CMAKE_SOURCE_DIR}/testing)
set(TESTING_BUILD ${TESTING_PATH}/build)
set(TESTING_BIN ${TESTING_PATH}/bin)

add_subdirectory(${TESTING_PATH} ${TESTING_BUILD})
create_symlink(${grammar_tester} ${TESTING_BIN})
