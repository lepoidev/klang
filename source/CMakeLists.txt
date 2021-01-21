set(KLANG_SOURCE_FILES
    ${KLANG_SOURCE_DIR}/main.cpp
    ${KLANG_SOURCE_DIR}/AST/Nodes/ASTNode.cpp
    ${KLANG_SOURCE_DIR}/AST/ASTGenerator.cpp
    ${KLANG_SOURCE_DIR}/AST/ASTVisitor.cpp
    ${KLANG_SOURCE_DIR}/IR/Tools/LoopBuilder.cpp
    ${KLANG_SOURCE_DIR}/IR/Tools/CondBuilder.cpp
    ${KLANG_SOURCE_DIR}/IR/IRGenerator.cpp
)

target_sources(${compiler} PUBLIC ${KLANG_SOURCE_FILES})