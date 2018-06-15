if (SHIVA_USE_SFML_AS_RENDERER)
    add_executable(sfml-example sfml-example.cpp sfml-example.hpp)
    target_link_libraries(sfml-example shiva::shiva)
endif()