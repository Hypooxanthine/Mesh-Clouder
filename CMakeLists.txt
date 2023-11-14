cmake_minimum_required(VERSION 3.10)

project(MeshClouder)

if (POLICY CMP0072)
    cmake_policy (SET CMP0072 NEW)
endif(POLICY CMP0072)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++23 -Wall -Wno-volatile")

# Project directories
set(SOURCE_DIR src)
set(INCLUDE_DIR include)

# Dependencies include directories
set(OBJLOADER_INCLUDE_DIR dependencies/OBJ_Loader/include)
set(HAPPLY_INCLUDE_DIR dependencies/happly/include)
set(GLM_INCLUDE_DIR dependencies/GLM/include)
set(IMGUI_INCLUDE_DIR dependencies/ImGui/include)
set(STB_IMAGE_INCLUDE_DIR dependencies/stb_image/include)
if(WIN32)
    set(GLEW_INCLUDE_DIR dependencies/GLEW/include)
    set(GLFW_INCLUDE_DIR dependencies/GLFW/include)
    set(OSDIALOG_INCLUDE_DIR )
elseif(UNIX)
    set(GLEW_INCLUDE_DIR )
    set(GLFW_INCLUDE_DIR )
    set(OSDIALOG_INCLUDE_DIR dependencies/osdialog/include)
endif(WIN32)

# Dependencies lib directories
if(WIN32)
    set(GLFW_LIBRARY ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib-mingw-w64/libglfw3.a)
    set(GLEW_LIBRARY ${CMAKE_SOURCE_DIR}/dependencies/GLEW/lib/Mingw64/libglew32.a opengl32)
elseif(UNIX)
    set(GLFW_LIBRARY glfw3 X11)
    set(GLEW_LIBRARY GLEW)
endif(WIN32)

# Implementations
    # Libs
set(IMGUI_IMPL
    dependencies/ImGui/src/imgui_demo.cpp
    dependencies/ImGui/src/imgui_draw.cpp
    dependencies/ImGui/src/imgui_tables.cpp
    dependencies/ImGui/src/imgui_widgets.cpp
    dependencies/ImGui/src/imgui.cpp
    dependencies/ImGui/src/impl/imgui_impl_glfw.cpp
    dependencies/ImGui/src/impl/imgui_impl_opengl3.cpp
)
set(STB_IMAGE_IMPL dependencies/stb_image/src/stb_image.cpp)
if(WIN32)
    set(OSDIALOG_IMPL )
elseif(UNIX)
    set(OSDIALOG_IMPL
        dependencies/osdialog/src/osdialog.c
        dependencies/osdialog/src/osdialog_gtk2.c
    )
endif(WIN32)
    # Project
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
    ${SOURCE_DIR}/Rendering/Renderer.cpp
    ${SOURCE_DIR}/Rendering/Abstraction/IndexBuffer.cpp
    ${SOURCE_DIR}/Rendering/Abstraction/Shader.cpp
    ${SOURCE_DIR}/Rendering/Abstraction/Texture.cpp
    ${SOURCE_DIR}/Rendering/Abstraction/VertexArray.cpp
    ${SOURCE_DIR}/Rendering/Abstraction/VertexBuffer.cpp
    ${SOURCE_DIR}/Rendering/Abstraction/VertexBufferLayout.cpp
    ${SOURCE_DIR}/Rendering/Objects/Camera.cpp
    ${SOURCE_DIR}/Rendering/Objects/RenderObject.cpp
    ${SOURCE_DIR}/Rendering/Objects/RenderMesh.cpp
    ${SOURCE_DIR}/Rendering/Objects/RenderGrid.cpp
    ${SOURCE_DIR}/Rendering/Objects/MeshGenerator.cpp
    ${SOURCE_DIR}/Editor/ObjectEditor.cpp
    ${SOURCE_DIR}/Math/Math.cpp
)

set(SOURCES
    ${IMGUI_IMPL}
    ${OSDIALOG_IMPL}
    ${STB_IMAGE_IMPL}
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
    ${OSDIALOG_INCLUDE_DIR}
    ${STB_IMAGE_INCLUDE_DIR}
)

include_directories(meshclouder PUBLIC 
    ${INCLUDES}
)

add_executable(meshclouder ${SOURCES})

add_definitions(-D GLEW_STATIC)

target_link_libraries(meshclouder
    ${OPENGL_LIBRARY}
    ${GLFW_LIBRARY}
    ${GLEW_LIBRARY}
)

if(UNIX)
    # Include GTK
    find_package(PkgConfig)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    add_definitions(${GTK3_CFLAGS_OTHER})

    # Add GTK as a dependency
    target_link_libraries(meshclouder ${GTK3_LIBRARIES})
    unset(GTK_PATH)
endif(UNIX)