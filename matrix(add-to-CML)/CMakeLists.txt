add_library(matrix INTERFACE)
target_include_directories(matrix INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)
target_compile_features(matrix INTERFACE cxx_std_17