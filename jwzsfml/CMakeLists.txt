add_library(jwzsfml INTERFACE)
target_include_directories(jwzsfml INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)
target_compile_features(jwzsfml INTERFACE cxx_std_17)