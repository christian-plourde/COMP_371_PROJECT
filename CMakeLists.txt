cmake_minimum_required(VERSION 3.13)
project(COMP_371_PROJECT)

set(CMAKE_CXX_STANDARD 14)

add_executable(COMP_371_PROJECT main.cpp Utilities/SceneElements/Camera.cpp Utilities/Math/Vectors.cpp Utilities/SceneElements/Plane.cpp Utilities/SceneElements/Sphere.cpp Utilities/SceneElements/Mesh.cpp Utilities/SceneElements/Light.cpp Utilities/SceneLoader.cpp Utilities/Math/Matrices.cpp Utilities/Math/RayTracer.cpp Utilities/Math/Ray.cpp)