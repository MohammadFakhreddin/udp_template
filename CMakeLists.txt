cmake_minimum_required(VERSION VERSION 3.16.0)

project ("CrazyTankGameProject" C CXX)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Just for submodules in case we need it ######################

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

###############################################################

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS TRUE)
endif()

if(MSVC)
    add_definitions (-D_CRT_SECURE_NO_WARNINGS)
    add_definitions (/MDd)
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

if(${CMAKE_BUILD_TYPE} MATCHES Release)
    add_definitions(-DNDEBUG)
    message(STATUS "Runnning on release mode")
    message(STATUS ${CMAKE_CXX_FLAGS_RELEASE})
else()
    add_definitions(-D_DEBUG)
    message(STATUS "Running on debug mode")
    message(STATUS ${CMAKE_CXX_FLAGS_DEBUG})
endif()

if(LINUX)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

###############################################################

find_package(OpenMP REQUIRED)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
link_libraries(OpenMP::OpenMP_CXX)

### Bedrock ################################################

add_subdirectory("${CMAKE_SOURCE_DIR}/src/bedrock")
include_directories("${CMAKE_SOURCE_DIR}/src/bedrock")
link_libraries(Bedrock)

### Time ###################################################

add_subdirectory("${CMAKE_SOURCE_DIR}/src/time_system")
include_directories("${CMAKE_SOURCE_DIR}/src/time_system")
link_libraries(TimeSystem)

### JobSystem ###################################################

add_subdirectory("${CMAKE_SOURCE_DIR}/src/job_system")
include_directories("${CMAKE_SOURCE_DIR}/src/job_system")
link_libraries(JobSystem)

### Executables ############################################

add_subdirectory("${CMAKE_SOURCE_DIR}/executable/client")
add_subdirectory("${CMAKE_SOURCE_DIR}/executable/server")

############################################################

message(STATUS "Cmake process is complete!")
