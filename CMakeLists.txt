cmake_minimum_required(VERSION 4.2.0)

project(libkpi
	VERSION ${KPI_VERSION}
	LANGUAGES C)

add_library(kpi STATIC
	src/kpi.c
)

target_compile_options(kpi PRIVATE
	-Wall
	-Wextra
	-pedantic
)

target_include_directories(kpi 
	PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/kpi>
)
target_include_directories(kpi PRIVATE src)



# Installation
include(CMakePackageConfigHelpers)
configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/kpiConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/kpiConfig.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kpi
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/kpiConfigVersion.cmake
    VERSION ${KPI_VERSION}
    COMPATIBILITY AnyNewerVersion
)

include(GNUInstallDirs)
install(
	TARGETS kpi
	EXPORT kpiTargets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
	DIRECTORY include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/kpi
)

install(
	EXPORT kpiTargets
	NAMESPACE kpi::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kpi
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/kpiConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/kpiConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kpi
)
