# CMakeLists.txt
zephyr_library()
zephyr_library_sources(src/behaviors/behavior_cycle_animation.c)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/include)