# CMakeLists.txt at repo root (module)
zephyr_library()

zephyr_library_sources(
    boards/shields/nice_view_gem/widgets/animation.c
    boards/shields/nice_view_gem/widgets/animation_assets.c
    src/behaviors/behavior_cycle_animation.c
)

zephyr_include_directories(boards/shields/nice_view_gem/widgets)