# Find QWT package - vcpkg provides unofficial-qwt, try it first
find_package(unofficial-qwt CONFIG QUIET)

if(unofficial-qwt_FOUND)
    # vcpkg's qwt uses unofficial::qwt::qwt target, create an alias for compatibility
    if(NOT TARGET qwt::qwt)
        add_library(qwt::qwt ALIAS unofficial::qwt::qwt)
    endif()
    set(Qwt_FOUND TRUE)
    get_target_property(QWT_INCLUDE_DIR unofficial::qwt::qwt INTERFACE_INCLUDE_DIRECTORIES)
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