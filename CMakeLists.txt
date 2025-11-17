# CMakeLists.txt
zephyr_library()

# Add C sources
zephyr_library_sources(
    src/behaviors/behavior_cycle_animation.c
)
zephyr_library_include_directories(include)

zephyr_library_include_directories(${ZMK_CONFIG}/include)