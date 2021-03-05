cmake_minimum_required(VERSION 3.19)

project(generator)

add_executable("generator" "src/main.cpp" "src/Box.cpp" "include/Box.h" "src/Sphere.cpp" "include/Sphere.h" "src/Cone.cpp" "include/Cone.h" "src/Plane.cpp" "include/Plane.h" "src/Ponto3D.cpp" "include/Ponto3D.h" "src/Triangulo.cpp" "include/Triangulo.h")