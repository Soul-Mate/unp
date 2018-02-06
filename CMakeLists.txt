PROJECT(unp)

# add some macro define
# if define  DEBUG, will see debug info
ADD_DEFINITIONS(-DDEBUG -D_GNU_SOURCE)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)

# lib dir
SET(LIB_DIR ${PROJECT_SOURCE_DIR}/libs)

# set libs output dir
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

# set bin output dir
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


SET(LIBUNP_SRC ${LIB_DIR}/unp_err.c ${LIB_DIR}/unp_wsock.c
        ${LIB_DIR}/unp_readline.c ${LIB_DIR}/unp_readn.c
        ${LIB_DIR}/unp_writen.c ${LIB_DIR}/unp_wunix.c)

ADD_LIBRARY(unp SHARED ${LIBUNP_SRC})

ADD_SUBDIRECTORY(tests)

ADD_SUBDIRECTORY(ch1)

ADD_SUBDIRECTORY(ch3)

ADD_SUBDIRECTORY(ch5)

ADD_SUBDIRECTORY(ch6)