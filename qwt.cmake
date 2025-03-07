# Find QWT package
find_package(Qwt REQUIRED)

if(NOT Qwt_FOUND)
    message(FATAL_ERROR "QWT library not found")
endif()

# If custom QWT path is needed, uncomment and modify these lines:
# set(QWT_ROOT_DIR "path/to/qwt")
# set(QWT_INCLUDE_DIR "${QWT_ROOT_DIR}/include")
# set(QWT_LIBRARY_DIR "${QWT_ROOT_DIR}/lib")

# Add QWT to include path
include_directories(${QWT_INCLUDE_DIR})

# Link directories if needed
if(QWT_LIBRARY_DIR)
    link_directories(${QWT_LIBRARY_DIR})
endif() 