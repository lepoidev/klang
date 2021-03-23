include(ExternalProject)

set(AST_BASE_VISITOR_HEADER "${KLANG_INCLUDE_DIR}/AST/Visitor/BaseVisitor.h")

file(GLOB files "${KLANG_INCLUDE_DIR}/AST/Nodes/*.h")
file(WRITE "${AST_BASE_VISITOR_HEADER}" "#pragma once\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "\n// This file is automatically generated. Do not edit.\n\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "#include \"AST/Visitor/Visitor.h\"\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "#include \"AST/ASTNodes.h\"\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "\nnamespace AST\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "{\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "  class BaseVisitor : public Visitor\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "  {\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "  public:\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "    std::any VisitChildren( Node& node ) override\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "    {\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "      for( auto& child : node.GetChildren() )\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "      {\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "        if( child != nullptr )\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "        {\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "          child->Accept( *this );\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "        }\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "      }\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "      return {};\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "    }\n")
foreach(file ${files})
    string(REPLACE "${KLANG_INCLUDE_DIR}/AST/Nodes/" "" NODE_FILE "${file}")
    string(REPLACE ".h" "" NODE_FILE "${NODE_FILE}")
    file(APPEND "${AST_BASE_VISITOR_HEADER}" "    std::any Visit( ${NODE_FILE}& node ) override { return VisitChildren( node ); }\n")
endforeach()
file(APPEND "${AST_BASE_VISITOR_HEADER}" "  };\n")
file(APPEND "${AST_BASE_VISITOR_HEADER}" "}\n")