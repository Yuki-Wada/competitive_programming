cmake_minimum_required(VERSION 2.8)
add_executable(at_coder src/main.cpp src/algorithm.cpp src/data_structure.cpp src/graph.cpp src/mod.cpp src/input.txt)
add_executable(marathon_solver src/marathon_main.cpp src/marathon_input.txt src/marathon_output.txt)
add_executable(marathon_checker src/output_checker.cpp src/marathon_input.txt src/marathon_output.txt)
