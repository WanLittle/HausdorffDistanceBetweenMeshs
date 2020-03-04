cmake_minimum_required(VERSION 2.6)

Project(HasudorffDistanceBetweenMeshs)

file(GLOB_RECURSE PROJECT_SOURCES src/*.c src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS src/*.h)

find_package(OpenMP)
if(OPENMP_FOUND)
	message("OPENMP FOUND")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
	message("OPENMO NOT FOUND")
endif()

add_executable(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES})