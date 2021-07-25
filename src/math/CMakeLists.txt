cmake_minimum_required(VERSION 3.5)
project(math)

set(math_MAJOR_VERSION 0)
set(math_MINOR_VERSION 0)
set(math_PATCH_VERSION 0)
set(math_VERSION
  ${math_MAJOR_VERSION}.${math_MINOR_VERSION}.${math_PATCH_VERSION})

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(${PROJECT_NAME} 
  src/math.cpp
  # ...
)

target_link_directories(${PROJECT_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)


include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
  EXPORT mathTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT mathTargets
  FILE mathTargets.cmake
  NAMESPACE math::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/math
)

include(CMakePackageConfigHelpers)

# Generate the version file for the config file which will
# be checked by find_package
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/mathConfigVersion.cmake"
  VERSION "${math_VERSION}"
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/mathConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/math
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/mathConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/math
)
