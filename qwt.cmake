# Find QWT package - vcpkg provides unofficial-qwt, try it first
find_package(unofficial-qwt CONFIG QUIET)

if(unofficial-qwt_FOUND)
    # vcpkg's qwt port has a bug where INTERFACE_INCLUDE_DIRECTORIES contains "//include".
    # Filter out invalid paths and add the correct one.
    get_target_property(_qwt_includes unofficial::qwt::qwt INTERFACE_INCLUDE_DIRECTORIES)
    set(_fixed_includes "")
    if(_qwt_includes)
        foreach(_dir IN LISTS _qwt_includes)
            if(EXISTS "${_dir}")
                list(APPEND _fixed_includes "${_dir}")
            endif()
        endforeach()
    endif()

    # If no valid include dir was found, search manually in CMAKE_PREFIX_PATH
    if(NOT _fixed_includes)
        foreach(_prefix IN LISTS CMAKE_PREFIX_PATH)
            if(EXISTS "${_prefix}/include/qwt.h")
                list(APPEND _fixed_includes "${_prefix}/include")
                break()
            elseif(EXISTS "${_prefix}/include/qwt/qwt.h")
                list(APPEND _fixed_includes "${_prefix}/include/qwt")
                break()
            endif()
        endforeach()
    endif()

    if(_fixed_includes)
        set_target_properties(unofficial::qwt::qwt PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${_fixed_includes}"
        )
    endif()

    # Also fix IMPORTED_LOCATION if missing (vcpkg qwt port may not set it)
    get_target_property(_qwt_location unofficial::qwt::qwt IMPORTED_LOCATION)
    if(NOT _qwt_location)
        foreach(_prefix IN LISTS CMAKE_PREFIX_PATH)
            if(EXISTS "${_prefix}/lib/qwt.lib")
                set_target_properties(unofficial::qwt::qwt PROPERTIES
                    IMPORTED_LOCATION "${_prefix}/lib/qwt.lib"
                )
                break()
            elseif(EXISTS "${_prefix}/lib/qwt6.lib")
                set_target_properties(unofficial::qwt::qwt PROPERTIES
                    IMPORTED_LOCATION "${_prefix}/lib/qwt6.lib"
                )
                break()
            endif()
        endforeach()
    endif()

    # Create a compatible alias for the rest of the project
    if(NOT TARGET qwt::qwt)
        add_library(qwt::qwt ALIAS unofficial::qwt::qwt)
    endif()
    set(Qwt_FOUND TRUE)
    set(QWT_INCLUDE_DIR "${_fixed_includes}")
else()
    # Fallback for non-vcpkg environments
    find_package(Qwt REQUIRED)
    if(NOT Qwt_FOUND)
        message(FATAL_ERROR "QWT library not found")
    endif()
    if(NOT QWT_INCLUDE_DIR AND TARGET qwt::qwt)
        get_target_property(QWT_INCLUDE_DIR qwt::qwt INTERFACE_INCLUDE_DIRECTORIES)
    endif()
endif()

# Add QWT to include path
if(QWT_INCLUDE_DIR)
    include_directories(${QWT_INCLUDE_DIR})
endif()

# Link directories if needed
if(QWT_LIBRARY_DIR)
    link_directories(${QWT_LIBRARY_DIR})
endif()
