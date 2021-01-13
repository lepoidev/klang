include(ExternalProject)

if (NOT EXISTS "${ANTLR4_JAR}")
    message(STATUS "Downloading ${ANTLR4_JAR_NAME}")
    file(
            DOWNLOAD
            "https://www.antlr.org/download/${ANTLR4_JAR_NAME}"
            "${ANTLR4_JAR}"
            SHOW_PROGRESS
    )
endif()