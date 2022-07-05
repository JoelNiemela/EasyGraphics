cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Demo VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRC
     "src/*.h"
     "src/*.cpp"
     "src/**/*.h"
     "src/**/*.cpp"
)

include_directories(../src)
include_directories(../vendor)
include_directories(../vendor/glfw/include)

file(GLOB IMGUI
     "vendor/imgui/*.h"
     "vendor/imgui/*.cpp"
)

file(GLOB STB
     "vendor/stb/*.h"
     "vendor/stb/*.c"
)

add_executable(Demo ${SRC} ${IMGUI} ${STB})

target_link_libraries(${PROJECT_NAME} GL)

find_library(GLFW glfw PATH vendor/glfw)

target_link_libraries(Demo ${OPENGL_LIBRARIES} glfw)

find_library(GLEW GLEW PATH vendor/glew-2.2.0/lib)

target_link_libraries(Demo ${GLEW})

find_library(EasyGraphics eg PATH ..)

target_link_libraries(Demo ${EasyGraphics})
