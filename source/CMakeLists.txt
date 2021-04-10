set(KLANG_SOURCE_FILES
    ${KLANG_SOURCE_DIR}/main.cpp
    ${KLANG_SOURCE_DIR}/AST/ASTGenerator.cpp
    ${KLANG_SOURCE_DIR}/AST/TypeResolver.cpp
    ${KLANG_SOURCE_DIR}/IR/IRGenerator.cpp
)

target_sources(${compiler} PUBLIC ${KLANG_SOURCE_FILES})