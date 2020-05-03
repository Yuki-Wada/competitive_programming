cmake_minimum_required(VERSION 2.8)
add_executable(at_coder src/main.cpp src/data_structure.cpp src/graph.cpp src/algorithm.cpp input.txt)
add_executable(marathon_solver src/asprova6.cpp input.txt output.txt)
add_executable(marathon_checker src/output_checker.cpp input.txt output.txt)
