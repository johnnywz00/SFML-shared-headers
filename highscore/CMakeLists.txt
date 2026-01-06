add_library(high_score INTERFACE)
target_include_directories(high_score INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)
target_compile_features(high_score INTERFACE cxx_std_17)