cmake_minimum_required(VERSION 3.10)

project(gl_util VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Include GLFW
find_package(glfw3 REQUIRED)

# Include neccessary path
set(PATH_3RDPARTY "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty")

set(GLAD_PATH ${PATH_3RDPARTY}/glad/ CACHE INTERNAL "GLAD path")

set(INC_PATH ${GLAD_PATH}include/ CACHE INTERNAL "include path")
list(APPEND INC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/gl_util/")
list(APPEND INC_PATH ${PATH_3RDPARTY}/stb_image/)
list(APPEND INC_PATH ${PATH_3RDPARTY}/glm/)
# message("Include path: ${INC_PATH}")

# The GL utility sources
file(GLOB GL_UTIL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC
    ${GL_UTIL_SRC}
    ${PATH_3RDPARTY}/glad/src/glad.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        ${INC_PATH}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/>
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
