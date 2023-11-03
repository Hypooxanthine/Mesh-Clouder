# MeshClouder

MeshClouder is a standalone program developed in C++ for Linux. It allows you to transform 3D mesh files (in .obj and .ply formats) into point clouds. The project aims to provide a user-friendly graphical interface to facilitate the conversion process. Users can adjust various parameters for the mesh-to-point cloud conversion and export the resulting point cloud as a .ply file.

## Features

- Import mesh files in .obj and .ply formats.
- Convert mesh files to point clouds.
- User-friendly graphical interface.
- Parameter adjustments for conversion.
- Export point clouds as .ply files.

## Dependencies

- CMake

### TODO

List all the packages needed. Should be done very soon, I need to configure a virtual machine with fresh ubuntu set up on it so I can see all the needed packages.

## Building and Running

Use CMake to configure and build the project for your platform.

Linux terminal or VSCode embedded terminal on Linux:

```bash
mkdir build
cd build
cmake ..
make
```

VSCode on Windows:

- Install "CMake Tools" extension.
- Configure then build all projects on CMake Tools' menu.

The executable will be created in the build directory.

## Usage

## Known problems

On Linux with VSCode, environement variable "GTK_PATH" needs to be unset at start of each session. GTK will also complain about canberra-gtk-module failed to be loaded. It does not appear outside of VSCode.
Disabling GTK_PATH in VSCode embedded terminal :

```bash
unset GTK_PATH
```