set(TARGET_NAME lab4)
set(${TARGET_NAME}_SRC_DIR ${PROJECT_SOURCE_DIR}/${TARGET_NAME})

file(GLOB_RECURSE ${TARGET_NAME}_SRC_LIST
    ${${TARGET_NAME}_SRC_DIR}/*.h
    ${${TARGET_NAME}_SRC_DIR}/*.cpp
    )

add_executable(${TARGET_NAME} ${${TARGET_NAME}_SRC_LIST} ${UTILS_SRC_LIST})

if (NOT TARGET glfw)
    add_subdirectory(${PROJECT_SOURCE_DIR}/ext/glfw ${PROJECT_BINARY_DIR}/ext/glfw3)
endif()

target_link_libraries(${TARGET_NAME} PRIVATE glfw)

if (NOT TARGET freeglut)
    add_subdirectory(${PROJECT_SOURCE_DIR}/ext/glut ${PROJECT_BINARY_DIR}/ext/glut)
endif()

target_link_libraries(${TARGET_NAME} PRIVATE freeglut)

find_package(OpenGL REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${TARGET_NAME} PRIVATE OpenGL::GLU)
