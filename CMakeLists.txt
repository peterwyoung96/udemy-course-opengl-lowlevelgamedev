################################################################################
# Main CMake
# ===========
# This is my main cmake file for the project. This should help with the
# compiling and building process.
#
################################################################################

## MINIMUM VERSION OF CMAKE
cmake_minimum_required(VERSION 3.16)

## SET THE STANDARD USED FOR C++
set(CMAKE_CXX_STANDARD 17)

## LINK SOME TIME OPTIMIZATION
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

## SET A PROJECT NAME
project(mygame)

## ADD ALL THE THIRD-PARTY LIBRARIES
set(SDL_STATIC ON)

add_subdirectory(thirdparty/SDL-release-2.30.5)		#window opener
add_subdirectory(thirdparty/glad)			#opengl loader
add_subdirectory(thirdparty/stb_image)			#loading images
add_subdirectory(thirdparty/stb_truetype)		#loading ttf files
#add_subdirectory(thirdparty/enet-1.3.17)		#networking
add_subdirectory(thirdparty/glm)			#math
add_subdirectory(thirdparty/imgui-docking)		#ui

# GATHER ALL THE SOURCE FILES RECURSIVELY
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# SETUP THE EXECUTABLE AND ITS PROPERTIES
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# This makes sure that the asset path is copied to the
# root folder of the exe
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC 
    RESOURCES_PATH="./resources/"    
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC 
    PRODUCTION_BUILD=1
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MY_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# MAKE SURE TO LINK ALL THE LIBRARIES
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    glm 
    glad 
    stb_image 
    stb_truetype 
    imgui 
    SDL2main
    SDL2-static
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/resources"
    COMMENT "Copying resources to build directory..."
)

## EOF ##