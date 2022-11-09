# Get the GoogleTest
set(googletest "googletest")
FetchContent_Declare(
    ${googletest}
    GIT_REPOSITORY "https://github.com/google/googletest"
    GIT_TAG        release-1.11.0
    GIT_PROGRESS   true
)

FetchContent_GetProperties(${googletest})
if(NOT ${googletest}_POPULATED)
    set(FETCHCONTENT_QUIET OFF)
    FetchContent_Populate(${googletest})
    add_subdirectory(${${googletest}_SOURCE_DIR} ${${googletest}_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
