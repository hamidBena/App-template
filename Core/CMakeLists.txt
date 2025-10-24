#    ---- Core ----
# static library for core functionalities

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(Core STATIC)

target_sources(Core PRIVATE ${SOURCES})

# organize files in IDE (like Visual Studio)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_include_directories(Core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(Core PUBLIC SFML::Graphics SFML::Window MyUI)