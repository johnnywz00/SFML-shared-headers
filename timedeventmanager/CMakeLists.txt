add_library(timed_event_manager INTERFACE)
target_include_directories(timed_event_manager INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)
target_compile_features(timed_event_manager INTERFACE cxx_std_17)