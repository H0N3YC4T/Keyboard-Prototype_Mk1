# CMakeLists.txt at repo root (module)
zephyr_library()
zephyr_include_directories($ENV{ZMK_CONFIG}/../zmk/app/include)
zephyr_include_directories(${ZMK_DIR}/app/include)
zephyr_include_directories(${ZEPHYR_BASE}/../zmk/app/include)

zephyr_library_sources(src/behaviors/behavior_cycle_animation.c)
zephyr_include_directories(boards/shields/nice_view_gem/widgets)