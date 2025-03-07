cmake_minimum_required(VERSION 3.30.5)

# Set project name and language
project(LightYears
	LANGUAGES C CXX
	VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD               14)
set(CMAKE_CXX_STANDARD_REQUIRED      ON)
set(CMAKE_CXX_EXTENSIONS            OFF)

#this flag is because some SFML files using objective C flags and the compiler doesnt know
#what to do with these so it throws an error. this lets it ignore the error and it seems to be
#working for now - the sfml is linked and built properly
add_compile_options(-Wno-unused-command-line-argument)

set_property(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LightYearsGame)

include(FetchContent)

set(SFML_LIB_NAME SFML)

FetchContent_Declare(
	${SFML_LIB_NAME}
	GIT_REPOSITORY https://github.com/SFML/SFML
	GIT_TAG 2.6.0
	GIT_SHALLOW FALSE
)
 
FetchContent_MakeAvailable(${SFML_LIB_NAME})

set(LIGHT_YEARS_ENGINE_TARGET_NAME LighYearsEngine)
set(LIGHT_YEARS_GAME_TARGET_NAME LighYearsGame)

add_subdirectory(LightYearsEngine)
add_subdirectory(LightYearsGame)
