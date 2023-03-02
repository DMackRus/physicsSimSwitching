cmake_minimum_required(VERSION 3.24)
project(physicsSimSwitching)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    message(STATUS "OPENMP has been found")
endif()

set(Eigen3_FOUND True)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
if (TARGET Eigen3::Eigen)
    # Use the imported target
    message(STATUS "Eigen library found")
else()
    message(STATUS "could not find eigen library")
endif (TARGET Eigen3::Eigen)


set(Mujoco_INCLUDE_DIRS /home/dave/Libraries/mujoco/include)
find_library(GLFW libglfw.so.3 HINTS /home/dave/Libraries/mujoco/include)
message(STATUS "GLFW lib found at: " ${GLFW})

file(GLOB LIB_MUJOCO /home/dave/Libraries/mujoco/include/libmujoco.so)
message(STATUS "MuJoCo lib found at: " ${LIB_MUJOCO})

message(STATUS "Mujoco include directory: " ${Mujoco_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp
                physicsSimulators/physicsSimulator.cpp physicsSimulators/physicsSimulator.h
                stdInclude/stdInclude.h
        physicsSimulators/MuJoCoHelper.cpp physicsSimulators/MuJoCoHelper.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${Mujoco_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} Eigen3::Eigen ${LIB_MUJOCO} ${GLFW} libGL.so GL)