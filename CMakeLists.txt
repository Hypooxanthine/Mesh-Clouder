cmake_minimum_required(VERSION 3.10)

project(MeshClouder)

if (POLICY CMP0072)
    cmake_policy (SET CMP0072 NEW)
endif(POLICY CMP0072)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++23 -Wall")

# Project directories
set(SOURCE_DIR src)
set(INCLUDE_DIR include)

# Dependencies include directories
set(OBJLOADER_INCLUDE_DIR dependencies/OBJ_Loader/include)
set(HAPPLY_INCLUDE_DIR dependencies/happly/include)
set(GLEW_INCLUDE_DIR dependencies/GLEW/include)
set(GLM_INCLUDE_DIR dependencies/GLM/include)
set(IMGUI_INCLUDE_DIR dependencies/ImGui/include)
if(WIN32)
    set(GLFW_INCLUDE_DIR dependencies/GLFW/include)
elseif(UNIX)
    set(GLFW_INCLUDE_DIR )
endif(WIN32)

# Dependencies lib directories
if(WIN32)
    set(GLFW_LIBRARY ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib-mingw-w64/libglfw3.a)
    set(GLEW_LIBRARY ${CMAKE_SOURCE_DIR}/dependencies/GLEW/lib/Release/x64/glew32s.lib)
endif(WIN32)

if(UNIX)
    set(GLFW_LIBRARY glfw3 X11)
    set(GLEW_LIBRARY GLEW)
endif(UNIX)

# Implementations
set(IMGUI_IMPL
    dependencies/ImGui/src/imgui_demo.cpp
    dependencies/ImGui/src/imgui_draw.cpp
    dependencies/ImGui/src/imgui_tables.cpp
    dependencies/ImGui/src/imgui_widgets.cpp
    dependencies/ImGui/src/imgui.cpp
    dependencies/ImGui/src/impl/imgui_impl_glfw.cpp
    dependencies/ImGui/src/impl/imgui_impl_opengl3.cpp
)

set(PROJECT_IMPL
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/Core/Application.cpp
    ${SOURCE_DIR}/States/State.cpp
    ${SOURCE_DIR}/States/MainState.cpp
    ${SOURCE_DIR}/Data/Mesh.cpp
    ${SOURCE_DIR}/Data/PointCloud.cpp
    ${SOURCE_DIR}/ExternalData/ObjectLoader.cpp
    ${SOURCE_DIR}/ExternalData/FileExplorer_Unix.cpp
    ${SOURCE_DIR}/ExternalData/FileExplorer_Windows.cpp
)

set(SOURCES
    ${IMGUI_IMPL}
    ${PROJECT_IMPL}
)

set(INCLUDES
    ${INCLUDE_DIR}
    ${OBJLOADER_INCLUDE_DIR}
    ${HAPPLY_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
)

include_directories(meshclouder PUBLIC 
    ${INCLUDES}
)

add_executable(meshclouder ${SOURCES})

add_definitions(-DGLEW_STATIC=1)

target_link_libraries(meshclouder
    ${OPENGL_LIBRARY}
    ${GLFW_LIBRARY}
    ${GLEW_LIBRARY}
)