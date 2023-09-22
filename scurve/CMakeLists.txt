
add_library(scurve STATIC)

target_sources(scurve
PUBLIC
    scurve.cpp
)

target_include_directories(scurve
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)