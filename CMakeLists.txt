cmake_minimum_required(VERSION 3.16)
project(bff_alg)

set(CMAKE_CXX_STANDARD 14)

add_executable(bff_alg src/main.cpp src/utils/FileUtil.h src/utils/FileUtil.cpp src/combinations/combinations.hpp src/combinations/combinations_init.hpp src/algorithm/BonSolver.cpp src/algorithm/BonSolver.h src/algorithm/BFFSolver.cpp src/algorithm/BFFSolver.h src/algorithm/AlgUtils.cpp src/algorithm/AlgUtils.h)
