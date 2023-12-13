# MeshClouder

MeshClouder is a standalone program developed in C++ for Linux and Windows. It allows you to transform 3D mesh files (in .obj and .ply formats) into point clouds. The project aims to provide a user-friendly graphical interface to facilitate the conversion process. Users can adjust various parameters for the mesh-to-point cloud conversion and export the resulting point cloud as a .ply file.

## Features

- Import mesh files in .obj and .ply formats.
- Convert mesh files to point clouds.
- User-friendly graphical interface.
- Parameter adjustments for conversion.
- Export point clouds as .ply files.

## Dependencies for Linux users

### CMake

`sudo apt install cmake`

### glew

`sudo apt install libglew-dev`

### pkg-config

`sudo apt install pkg-config`

### gtk+-3.0

`sudo apt install libgtk-3-0 libgtk-3-dev`

### glfw

Since no package of glfw exists, you need to download glfw source code [here](https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.zip) and then compile it yourself. Open a terminal in extracted file root folder then type :

```bash
mkdir build
cd build
cmake ..
make && sudo make install
```

This will install glfw binaries on your system

## Building and Running

Use CMake to configure and build the project for your platform.

(From repository root folder)

Linux:

```bash
mkdir build
cd build
cmake ..
make
```

Windows:

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
make
```

The executable will be created in the build directory.

## Usage

### Viewport

- Orbit around the object while holding down the mouse wheel.

## Known problems

On Linux with VSCode, environement variable "GTK_PATH" *sometimes* needs to be unset at start of a session. GTK could also complain about canberra-gtk-module failed to be loaded. It does not appear outside of VSCode.
Disabling GTK_PATH in VSCode embedded terminal (you should store its value somewhere but it appears it recovers it on its own at start of each session on VSCode):

```bash
unset GTK_PATH
```
