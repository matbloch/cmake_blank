SET(LIB_NAME io)
SET(HEADER_PATH ${cmakeblank_SOURCE_DIR}/include/${LIB_NAME})
SET(TARGET_H
    ${HEADER_PATH}/talker.h
    # ${HEADER_PATH}/myheader2.h
)

SET(TARGET_SRC
    talker.cpp
    # mymain2.cpp
)

################################################################################
## Create library

# link internally (other project libraries)
SET(TARGET_LIBRARIES
    # io
)
# link externally (librarys included over "find_library(${libname})")
SET(TARGET_EXTERNAL_LIBRARIES
    # ${MATH_LIBRARY}
)

SETUP_LIBRARY(${LIB_NAME})

