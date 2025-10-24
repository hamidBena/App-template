# ---- App ----

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(App)
target_sources(App PRIVATE ${SOURCES})

# organize files in IDE (like Visual Studio)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_link_libraries(App Core SFML::Graphics SFML::Window)

target_include_directories(App PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")