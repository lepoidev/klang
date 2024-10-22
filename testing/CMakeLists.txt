set(TESTING_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TESTING_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/source)

# grammar tester
set(GRAMMAR_TESTER_SOURCE ${ANTLR4_CPP_GENERATED_SRC_DIR} ${TESTING_SOURCE}/IsValidGrammar.cpp ${TESTING_SOURCE}/GrammarVerifier.cpp)
add_executable(${grammar_tester} ${GRAMMAR_TESTER_SOURCE})
add_dependencies(${grammar_tester} ${parser})
target_link_libraries(${grammar_tester} antlr4_static)
target_link_libraries(${grammar_tester} ${parser})
target_include_directories(${grammar_tester} PUBLIC ${ANTLR4_INCLUDE_DIRS})
target_include_directories(${grammar_tester} PUBLIC ${ANTLR_KlangParser_OUTPUT_DIR})
target_include_directories(${grammar_tester} PUBLIC ${TESTING_PATH}/include)

# add passing grammar tests
add_grammar_tests_from_folder(${TESTING_PATH}/valid_tests "valid_grammar_" ${TESTING_BIN}/${grammar_tester} "")

# add failing grammar tests
add_grammar_tests_from_folder(${TESTING_PATH}/invalid_tests/grammar_failures "invalid_grammar_" ${TESTING_BIN}/${grammar_tester} "-i")

# add compile and run tests
add_compiled_tests_from_folder(${TESTING_PATH}/valid_tests/statements/conditionals "compile_and_run_" "$<TARGET_FILE:${compiler}>" "" FALSE)

add_compiled_tests_from_folder(${TESTING_PATH}/valid_tests/expr/built_in_types/int/decl "compile_and_run_" "$<TARGET_FILE:${compiler}>" "" FALSE)

add_compiled_tests_from_folder(${TESTING_PATH}/valid_tests/expr/built_in_types/int/loop "compile_and_run_" "$<TARGET_FILE:${compiler}>" "" FALSE)

add_compiled_tests_from_folder(${TESTING_PATH}/valid_tests/expr/built_in_types/int/op "compile_and_run_" "$<TARGET_FILE:${compiler}>" "" FALSE)

# add compile and fail tests
add_compiled_tests_from_folder(${TESTING_PATH}/invalid_tests/runtime_failures "compile_and_fail_" "$<TARGET_FILE:${compiler}>" "" TRUE)