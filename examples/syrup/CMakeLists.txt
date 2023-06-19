add_executable(syrup main.cpp)

add_custom_command(TARGET syrup POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_BINARY_DIR}/engine/$<TARGET_FILE_NAME:Maple::engine>"
        "$<TARGET_FILE_DIR:syrup>/$<TARGET_FILE_NAME:Maple::engine>")
