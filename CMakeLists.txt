# CMakeLists.txt
zephyr_library()

# Add C sources
zephyr_library_sources(
    src/behaviors/behavior_cycle_animation.c
)
zephyr_include_directories(include)
