cmake_minimum_required(VERSION 3.16)

project(RAYLIB_TEMPLATE_GAME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Ensure raylib is built as static lib
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Raylib as static lib" FORCE)

# set production flags
set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(thirdparty/raylib-5.5)
add_subdirectory(thirdparty/imgui-docking)
add_subdirectory(thirdparty/rlImgui)
add_subdirectory(thirdparty/FastNoiseSIMD)

add_executable(RAYLIB_TEMPLATE_GAME
    src/main.cpp
    src/entities/entity_array.h
    src/pch.h
    src/globals.h
    src/game_data.h
    src/game_context.h

    src/entities/entity.h
    src/entities/entity.cpp

    src/entities/components.h
    src/asset_manager.h
    src/asset_manager.cpp
    src/map.h src/map.cpp
    src/scenes/game_play_scene.h src/scenes/game_play_scene.cpp
    src/scenes/main_menu_scene.h src/scenes/main_menu_scene.cpp
    src/game_context.cpp
    src/editor.h src/editor.cpp
    src/systems/render_system.h src/systems/render_system.cpp


)

if(PRODUCTION_BUILD)
        # setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")

	# remove the option to debug asserts.
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)

else()
        # This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)

endif()


target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} ${MY_HEADERS})

if(MSVC) # If using the VS compiler...

        target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	if(PRODUCTION_BUILD)
	        #YOU CAN REMOVE THE CONSOLE WITH THIS LINE!
		set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
	endif()

elseif(MINGW) # Windows / MinGW GCC/Clang
        if(PRODUCTION_BUILD)
	        # Remove console on Windows under MinGW
		target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE
		        -mwindows
		)
	endif()

elseif(APPLE OR UNIX) # macOS / Linux
        if(PRODUCTION_BUILD)
	        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -s)
	endif()
endif()

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h)

# link libs
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib_static imgui rlimgui fastNoiseSIMD)


