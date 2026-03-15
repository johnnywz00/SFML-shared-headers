add_library(animations INTERFACE)
target_include_directories(animations INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)
target_compile_features(animations INTERFACE cxx_std_17