add_library(jwzhpp INTERFACE)
target_include_directories(jwzhpp INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)
target_compile_features(jwzhpp INTERFACE cxx_std_17