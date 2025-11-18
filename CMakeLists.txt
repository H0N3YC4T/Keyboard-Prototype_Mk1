# CMakeLists.txt at repo root (module)
zephyr_include_directories(include)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/include)
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

zephyr_library()

zephyr_library_sources($(shell find ${CMAKE_CURRENT_SOURCE_DIR}/app/src -name "*.c"))

set_source_files_properties(
        ${APPLICATION_SOURCE_DIR}/app/src/behaviors/behavior_cycle_animation.c
        TARGET_DIRECTORY app
        PROPERTIES HEADER_FILE_ONLY ON)
target_sources(app PRIVATE app/src/behaviors/behavior_cycle_animation.c)


