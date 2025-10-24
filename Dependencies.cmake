
include(FetchContent)

# SFML
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.x)
FetchContent_MakeAvailable(SFML)

# MyUI
FetchContent_Declare(MyUI
        GIT_REPOSITORY https://github.com/hamidBena/MyUI
        GIT_TAG main)
FetchContent_MakeAvailable(MyUI)
