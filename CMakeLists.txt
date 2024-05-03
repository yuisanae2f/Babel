cmake_minimum_required(VERSION 3.10)

# C Shared Project
project(ae2f_Babel VERSION 1.0 LANGUAGES C)

# Sources List for Project
set(SOURCES
    src/Transformer.c
)

# Headers for library
set(HEADERS
    include/ae2fLib/Babel/Transformer.h
    include/ae2fLib/Babel/Transformer.hpp
)

# Lib build
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# include directory
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# dependencies
target_link_libraries(ae2f_Babel PUBLIC 
    ae2f_Container
)

# install set
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES ${HEADERS} DESTINATION include/ae2fLib/Babel)