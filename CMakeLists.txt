cmake_minimum_required(VERSION 3.28)
project(GGoldrush LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main 
    src/assets/AssetsManager.cpp

    src/world/Tile.cpp
    src/world/World.cpp
    
    src/gui/box/Box.cpp

    src/gui/button/GenericButton.cpp
    src/gui/button/PlainButton.cpp
    src/gui/button/PlainTextButton.cpp

    src/gui/container/Container.cpp

    src/gui/font/FontManger.cpp

    src/gui/view/ViewBase.cpp
    src/gui/view/View.cpp

    src/main.cpp
)

target_include_directories(main PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(main PRIVATE sfml-graphics)
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
        VERBATIM)
endif()
