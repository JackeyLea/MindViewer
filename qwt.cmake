# Try vcpkg's unofficial-qwt first (just to verify it's installed)
find_package(unofficial-qwt CONFIG QUIET)

if(unofficial-qwt_FOUND)
    # vcpkg's unofficial-qwt target is buggy (contains "//include" and missing
    # IMPORTED_LOCATION). Instead of using it directly, we locate the headers
    # and library ourselves and create a clean imported target.

    # Find include directory
    set(QWT_INCLUDE_DIR "")
    foreach(_prefix IN LISTS CMAKE_PREFIX_PATH)
        if(EXISTS "${_prefix}/include/qwt.h")
            set(QWT_INCLUDE_DIR "${_prefix}/include")
            break()
        elseif(EXISTS "${_prefix}/include/qwt/qwt.h")
            set(QWT_INCLUDE_DIR "${_prefix}/include/qwt")
            break()
        endif()
    endforeach()

    # Find library
    set(QWT_LIBRARY "")
    foreach(_prefix IN LISTS CMAKE_PREFIX_PATH)
        if(EXISTS "${_prefix}/lib/qwt.lib")
            set(QWT_LIBRARY "${_prefix}/lib/qwt.lib")
            break()
        elseif(EXISTS "${_prefix}/lib/qwt6.lib")
            set(QWT_LIBRARY "${_prefix}/lib/qwt6.lib")
            break()
        endif()
    endforeach()

    if(NOT QWT_INCLUDE_DIR OR NOT QWT_LIBRARY)
        message(FATAL_ERROR "Found unofficial-qwt package but cannot locate qwt headers or library")
    endif()

    message(STATUS "QWT include dir: ${QWT_INCLUDE_DIR}")
    message(STATUS "QWT library: ${QWT_LIBRARY}")

    # Create our own clean target
    if(NOT TARGET qwt::qwt)
        add_library(qwt::qwt SHARED IMPORTED)
        set_target_properties(qwt::qwt PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${QWT_INCLUDE_DIR}"
            IMPORTED_LOCATION "${QWT_LIBRARY}"
        )
    endif()

    set(Qwt_FOUND TRUE)
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
