set(TARGET_NAME lab3)
set(${TARGET_NAME}_SRC_DIR ${PROJECT_SOURCE_DIR}/${TARGET_NAME})

file(GLOB_RECURSE ${TARGET_NAME}_SRC_LIST
    ${${TARGET_NAME}_SRC_DIR}/*.h
    ${${TARGET_NAME}_SRC_DIR}/*.cpp
    )

add_executable(${TARGET_NAME} ${${TARGET_NAME}_SRC_LIST} ${UTILS_SRC_LIST})

add_subdirectory(${PROJECT_SOURCE_DIR}/ext/FastNoise2 ${PROJECT_BINARY_DIR}/ext/FastNoise2)

message(${PROJECT_SOURCE_DIR}/ext/FastNoise2/include)
target_include_directories(${TARGET_NAME} SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/ext/FastNoise2/include)
target_link_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/ext/FastNoise2/src)
target_link_libraries(${TARGET_NAME} PRIVATE FastNoise2)