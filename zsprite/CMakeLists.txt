add_library(zsprite INTERFACE)
target_include_directories(zsprite INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)
target_compile_features(zsprite INTERFACE cxx_std_17)