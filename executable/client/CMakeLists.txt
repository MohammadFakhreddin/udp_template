########################################

set(EXECUTABLE "Client")

set(EXECUTABLE_RESOURCES)

list(
    APPEND EXECUTABLE_RESOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/ClientMain.cpp"
)

add_executable(${EXECUTABLE} ${EXECUTABLE_RESOURCES})


########################################