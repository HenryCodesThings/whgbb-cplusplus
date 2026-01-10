cmake_minimum_required(VERSION 3.28)
project(WorldsHardestGame LANGUAGES CXX)

# Output folder for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------ Fetch SFML ------------------
include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

# ------------------ Fetch ImGui ------------------
FetchContent_Declare(
    ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.1
)
FetchContent_MakeAvailable(ImGui)

# Set IMGUI_DIR **after** ImGui is available
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)

# ------------------ Fetch ImGui-SFML ------------------
FetchContent_Declare(
    ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v2.6
)
FetchContent_MakeAvailable(ImGui-SFML)

# ------------------ Add your executable ------------------
add_executable(WorldsHardestGame
    "src/main.cpp"
    "src/Level1.cpp"
    "src/Level2.cpp"
 "src/var.cpp")

# Link libraries
target_link_libraries(WorldsHardestGame PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    ImGui-SFML::ImGui-SFML
)
