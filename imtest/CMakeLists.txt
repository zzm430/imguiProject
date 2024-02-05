cmake_minimum_required(VERSION 3.27)
project(imtest)

set(CMAKE_CXX_STANDARD 11)

include_directories(imgui)

#add_executable(imtest main.cpp
#            imgui/imgui.cpp
#            imgui/imgui_demo.cpp
#            imgui/imgui_draw.cpp
#            imgui/imgui_impl_glfw.cpp
#             imgui/imgui_impl_opengl3.cpp)

file(GLOB IMGUI_SOURCES "imgui/*.cpp")
add_executable(imtest main.cpp ${IMGUI_SOURCES})

target_link_libraries(${PROJECT_NAME} GL GLU glfw3 X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor)