cmake_minimum_required(VERSION 3.28)
project(GGoldrush LANGUAGES CXX)

# Enforce C++17 standard for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(SFML)

# Fetch GoogleTest=
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
  GIT_SHALLOW ON
)

FetchContent_MakeAvailable(googletest)

# ------------------- Create Library with Common Sources -------------------

# Define the common library target
add_library(game_library STATIC
    src/assets/AssetsManager.cpp
    src/common/AnmatedSprite.cpp
    src/world/Object.cpp
    src/world/Tile.cpp
    src/world/Structure.cpp
    src/world/structures/Resourcer.cpp
    src/world/World.cpp
    src/world/ObjectsBuilder.cpp
    src/world/Camera.cpp
    src/world/Picker.cpp
    src/game/Player.cpp
    src/game/items/Item.cpp
    src/game/items/Storage.cpp
    src/gui/button/GenericButton.cpp
    src/gui/button/PlainButton.cpp
    src/gui/button/PlainTextButton.cpp
    src/gui/container/Container.cpp
    src/gui/font/FontManger.cpp
    src/gui/GUIBase.cpp
    src/gui/guis/game/panes/Actionbar.cpp
    src/gui/guis/game/GameGUI.cpp
    src/gui/Debug.cpp
)

# Add include directories for the game library
target_include_directories(game_library PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)

# Link SFML to the game library
target_link_libraries(game_library PUBLIC sfml-graphics)

# ------------------- Main Executable -------------------

add_executable(main 
    src/main.cpp
)

target_include_directories(main PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(main PRIVATE game_library)
target_compile_features(main PRIVATE cxx_std_17)

# Variables for source and destination paths
set(RES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/res)

# same as CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/res for Debug 
set(RES_DEST_DIR $<TARGET_FILE_DIR:main>/res)

# Custom command to copy the "res" directory to the output directory
add_custom_command(
    TARGET main
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RES_SOURCE_DIR}
        ${RES_DEST_DIR}
    COMMAND ${CMAKE_COMMAND} -E echo "Resource (res) files copied from: ${RES_SOURCE_DIR} to: ${RES_DEST_DIR}"
)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM
    )
endif()

# ----------------- Unit Testing Setup -----------------

# Create a target for tests
add_executable(unit_tests
    # Add your test files here
    tests/test_storage.cpp
    tests/test_item.cpp
    tests/test_gui_containers.cpp
    tests/test_gui_containers_customized.cpp
)

# Link GoogleTest and the main sources for testing
target_link_libraries(unit_tests PRIVATE
    game_library
    gtest gtest_main
)

target_include_directories(unit_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)

# Add custom command to copy resources after building the unit tests executable
add_custom_command(
    TARGET unit_tests
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RES_SOURCE_DIR}
        $<TARGET_FILE_DIR:unit_tests>/res
    COMMAND ${CMAKE_COMMAND} -E echo "Resource (res) files copied to test directory: $<TARGET_FILE_DIR:unit_tests>/res"
)


# Enable CTest to run the tests
enable_testing()

# Add tests
add_test(NAME UnitTests COMMAND unit_tests)

# Set the working directory to the same folder as the unit_tests executable
set_tests_properties(UnitTests PROPERTIES
    WORKING_DIRECTORY $<TARGET_FILE_DIR:unit_tests>
)