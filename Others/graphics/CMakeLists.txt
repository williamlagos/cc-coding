project(BoxGL)

cmake_minimum_required(VERSION 2.8)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

find_package(OpenGL REQUIRED)
find_package(Box2D REQUIRED)
find_package(GLUT REQUIRED)

set(GRAPHICS_LIBRARIES ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} ${BOX2D_LIBRARIES})
set(GRAPHICS_SOURCES physics.cc graphics.cc main.cc)

add_executable(graphics ${GRAPHICS_SOURCES})
target_link_libraries(graphics ${GRAPHICS_LIBRARIES})
