set(CMAKE_CXX_STANDARD 17)

##! Msvc flags info
# /Zi - Produces a program database (PDB) that contains type information and symbolic debugging information for use with the debugger.
# /FS - Allows multiple cl.exe processes to write to the same .pdb file
# /DEBUG - Enable debug during linking
# /Od - Disables optimization
# /Ox - Full optimization

##! Global Configuration
if (UNIX)
    set(STANDARD_UNIX_CXX_FLAGS "-Wall -Wextra -Wfatal-errors")
elseif(MSVC)
    add_compile_options("/std:c++latest")
endif()

##! Internal Debug configuration
macro(__internal_debug_unix_cxx_flags)
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 ${STANDARD_UNIX_CXX_FLAGS}")
endmacro()

macro(__internal_debug_msvc_cxx_flags)
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /FS /DEBUG /Od /MP /MDd")
endmacro()

macro(__internal_debug_cxx_flags)
    if (CLANG OR GCC)
        __internal_debug_unix_cxx_flags()
    elseif(MSVC)
        __internal_debug_msvc_cxx_flags()
    endif()
endmacro()

##! Internal Release configuration
macro(__internal_release_unix_cxx_flags)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native ${STANDARD_UNIX_CXX_FLAGS}")
endmacro()

macro(__internal_release_msvc_cxx_flags)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 -DNDEBUG /MP")
endmacro()

macro(__internal_release_cxx_flags)
    if (CLANG OR GCC)
        __internal_release_unix_cxx_flags()
    elseif(MSVC)
        __internal_release_msvc_cxx_flags()
    endif()
endmacro()

##! Compiler Configuration.
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
    __internal_debug_cxx_flags()
    MSG_YELLOW_BOLD(STATUS "CMAKE_CXX_FLAGS_DEBUG:" "${CMAKE_CXX_FLAGS_DEBUG}" "")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DRELEASE)
    __internal_release_cxx_flags()
    MSG_YELLOW_BOLD(STATUS "CMAKE_CXX_FLAGS_RELEASE:" "${CMAKE_CXX_FLAGS_RELEASE}" "")
endif()