project(Platform)

cmake_minimum_required(VERSION 2.8)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(GLUT REQUIRED)
find_package(SDL REQUIRED)

set(GRAPHICS_LIBRARIES ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} ${OPENAL_LIBRARY} ${SDL_LIBRARY} alut)
set(GRAPHICS_SOURCES platform.cc main.cc)

add_executable(platform ${GRAPHICS_SOURCES})
target_link_libraries(platform ${GRAPHICS_LIBRARIES})
