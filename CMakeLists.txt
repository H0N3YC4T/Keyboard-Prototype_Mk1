# CMakeLists.txt
zephyr_library()
zephyr_library_sources(src/behaviors/behavior_cycle_animation.c)

#zephyr_library_include_directories(/include)
zephyr_library_sources(include/animation.h)
zephyr_library_sources(include/util.h)
zephyr_library_sources(include/screen_peripheral.h)