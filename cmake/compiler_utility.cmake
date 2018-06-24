##! This macro will give to your binary some information after the compilation.

macro(target_add_build_information TARGET)
    if (MSVC)
        target_compile_options(${TARGET} PUBLIC /d2cgsummary)
    elseif (CLANG OR GCC)
        target_compile_options(${TARGET} PUBLIC -ftime-report)
    endif ()
endmacro()
