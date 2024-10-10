cmake_minimum_required(VERSION 3.0)
project(ffsuckpeg)

# Set C++ version to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV and project-specific headers
include_directories(${OpenCV_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

# Add executable target with both source files
add_executable(${PROJECT_NAME} src/main.cpp src/process.cpp src/convert.cpp)

# Link OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
