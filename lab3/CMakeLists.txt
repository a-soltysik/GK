set(TARGET_NAME lab3)
set(${TARGET_NAME}_SRC_DIR ${PROJECT_SOURCE_DIR}/${TARGET_NAME})

file(GLOB_RECURSE ${TARGET_NAME}_SRC_LIST
    ${${TARGET_NAME}_SRC_DIR}/*.h
    ${${TARGET_NAME}_SRC_DIR}/*.cpp
    )

add_executable(${TARGET_NAME} ${${TARGET_NAME}_SRC_LIST} ${UTILS_SRC_LIST})