# CMakeLists.txt at repo root (module)
zephyr_library()

zephyr_include_directories(${ZEPHYR_BASE}/../zmk/app/include)
target_sources(app PRIVATE src/behaviors/behavior_cycle_animation.c)

zephyr_include_directories(boards/shields/nice_view_gem/widgets)