set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

##! Msvc flags info
# /Zi - Produces a program database (PDB) that contains type information and symbolic debugging information for use with the debugger.
# /FS - Allows multiple cl.exe processes to write to the same .pdb file
# /DEBUG - Enable debug during linking
# /Od - Disables optimization
# /Ox - Full optimization
# /Oy- do not suppress frame pointers (recommended for debugging)

##! Global Configuration
if (UNIX)
    set(STANDARD_UNIX_CXX_FLAGS "-Wall -Wextra -Wfatal-errors -Wno-unknown-pragmas")
    if (CLANG)
        set(STANDARD_UNIX_CXX_FLAGS "${STANDARD_UNIX_CXX_FLAGS} -Weverything -Wno-exit-time-destructors -Wno-covered-switch-default -Wno-documentation-unknown-command -Wno-gnu-zero-variadic-macro-arguments -Wno-global-constructors -Wno-newline-eof -Wno-reserved-id-macro -Wno-deprecated -Wno-padded -Wno-c++98-compat-pedantic -Wno-c++98-compat -Wno-weak-vtables")
    endif()
elseif(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
    set(STANDARD_MSVC_CXX_FLAGS "/permissive- /wd4068")
    add_definitions(-DNOMINMAX)
endif()

##! Internal Debug configuration
macro(__internal_debug_unix_cxx_flags)
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 ${STANDARD_UNIX_CXX_FLAGS}")
endmacro()

macro(__internal_debug_msvc_cxx_flags)
    set(CMAKE_CXX_FLAGS_DEBUG "${STANDARD_MSVC_CXX_FLAGS} /Zi /FS /DEBUG /Od /MP /MDd /Oy-")
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
    set(CMAKE_CXX_FLAGS_RELEASE "${STANDARD_MSVC_CXX_FLAGS} /O2 -DNDEBUG /MP")
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
