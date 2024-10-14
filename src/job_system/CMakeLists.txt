
set(LIBRARY_SOURCES)

list(
    APPEND LIBRARY_SOURCES

    "${CMAKE_CURRENT_SOURCE_DIR}/ScopeProfiler.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ScopeProfiler.cpp"
)

set(LIBRARY_NAME "JobSystem")
add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/")
