# MeshClouder

MeshClouder is a standalone program developed in C++ for Linux. It allows you to transform 3D mesh files (in .obj and .ply formats) into point clouds. The project aims to provide a user-friendly graphical interface to facilitate the conversion process. Users can adjust various parameters for the mesh-to-point cloud conversion and export the resulting point cloud as a .ply file.

## Features

- Import mesh files in .obj and .plyformats.
- Convert mesh files to point clouds.
- User-friendly graphical interface.
- Parameter adjustments for conversion.
- Export point clouds as .ply files.

## Environment

Development takes place in Visual Studio Code with appropriate plugins to ensure cross-platform compatibility. Regular tests are conducted on Linux to verify the project's performance.

## Dependencies

- CMake

## Building and Running

Use CMake to configure and build the project for your platform.

For Linux:

```bash
mkdir build
cd build
cmake ..
make
```

The executable will be created in the build directory.

## Usage

