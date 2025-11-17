# CMakeLists.txt
zephyr_library()
zephyr_library_sources(src/behaviors/behavior_cycle_animation.c)

if(DEFINED ZMK_CONFIG)
zephyr_library_include_directories(${ZMK_CONFIG}/include)
endif()