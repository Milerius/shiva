set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/sfml/video)


set(MODULE_PUBLIC_SOURCES
        "${MODULE_PATH}/system-sfml-video.cpp"
        )

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/system-sfml-video.hpp"
        "${MODULE_PATH}/video_component_impl.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_SOURCES}
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})