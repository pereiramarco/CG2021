cmake_minimum_required(VERSION 3.19)

project(generator)

set (CMAKE_CXX_STANDARD 11)

add_executable("generator" "src/main.cpp" "src/Box.cpp" "include/Box.h" "src/Sphere.cpp" "include/Sphere.h" "src/Cone.cpp" "include/Cone.h" "src/Plane.cpp" "include/Plane.h" "../Utils/Ponto3D.cpp" "../Utils/Ponto3D.h" "../Utils/Triangulo.cpp" "../Utils/Triangulo.h" "src/Model.cpp" "include/Model.h")