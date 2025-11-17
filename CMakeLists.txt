# CMakeLists.txt
zephyr_library()
zephyr_library_sources(src/behaviors/behavior_cycle_animation.c)

zephyr_library_include_directories(${ZMK_CONFIG}/include)
