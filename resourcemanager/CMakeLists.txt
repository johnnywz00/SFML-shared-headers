add_library(resource_manager INTERFACE)
target_include_directories(resource_manager INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)
target_compile_features(resource_manager INTERFACE cxx_std_17)