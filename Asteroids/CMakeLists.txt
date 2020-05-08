# CMakeList.txt : CMake project for RPN, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)

# Add source to this project's executable.
conan_cmake_run(REQUIRES glfw/3.3.2@bincrafters/stable BASIC_SETUP BUILD missing)
conan_cmake_run(REQUIRES glew/2.1.0@bincrafters/stable BASIC_SETUP BUILD missing)
conan_cmake_run(REQUIRES glm/0.9.9.7 BASIC_SETUP BUILD missing)
conan_cmake_run(REQUIRES openal/1.19.1 BASIC_SETUP BUILD missing)
file (GLOB_RECURSE SourceFiles "*.cpp" "*.h")
add_executable(Asteroids ${SourceFiles})

set_property(TARGET Asteroids PROPERTY CXX_STANDARD 17)
set_property(TARGET Asteroids PROPERTY CXX_STANDARD_REQUIRED ON)

configure_file(./Shader/default.frag ${CMAKE_CURRENT_BINARY_DIR}/bin/default.frag COPYONLY)
configure_file(./Shader/default.vert ${CMAKE_CURRENT_BINARY_DIR}/bin/default.vert COPYONLY)

configure_file(./Shader/particle.frag ${CMAKE_CURRENT_BINARY_DIR}/bin/particle.frag COPYONLY)
configure_file(./Shader/particle.vert ${CMAKE_CURRENT_BINARY_DIR}/bin/particle.vert COPYONLY)

configure_file(./Shader/text.frag ${CMAKE_CURRENT_BINARY_DIR}/bin/text.frag COPYONLY)
configure_file(./Shader/text.vert ${CMAKE_CURRENT_BINARY_DIR}/bin/text.vert COPYONLY)
configure_file(./Text/font.dds ${CMAKE_CURRENT_BINARY_DIR}/bin/font.dds COPYONLY)

configure_file(./Audio/MenuSelect.wav ${CMAKE_CURRENT_BINARY_DIR}/bin/MenuSelect.wav COPYONLY)
configure_file(./Audio/Explosion.wav ${CMAKE_CURRENT_BINARY_DIR}/bin/Explosion.wav COPYONLY)
configure_file(./Audio/Shoot.wav ${CMAKE_CURRENT_BINARY_DIR}/bin/Shoot.wav COPYONLY)

# TODO: Add tests and install targets if needed.
target_link_libraries(Asteroids ${CONAN_LIBS})
