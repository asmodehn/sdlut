CMAKE_MINIMUM_REQUIRED ( VERSION 2.4)

#Project Definition
PROJECT(Math)

INCLUDE(../RageCommon.cmake)

#
# Defining built types
#

#
# Defining what needs to be built
#

FILE(GLOB HEADERS include/*.hh)
INCLUDE_DIRECTORIES( ${Math_BINARY_DIR}/include ${Math_SOURCE_DIR}/include )

FILE(GLOB SOURCES src/*.cc)
MERGE("${HEADERS}" "${SOURCES}" SOURCES)

ADD_LIBRARY(Math ${SOURCES})
#needed in case we dont have recognised file extension
SET_TARGET_PROPERTIES(Math PROPERTIES LINKER_LANGUAGE CXX)

#
# Defining a set of Tests
#

ADD_SUBDIRECTORY(test)

#
# Defining installation rules
#

INSTALL ( FILES ${HEADERS} DESTINATION ${SVN_REV}/include )

INSTALL	(
	TARGETS Math
	RUNTIME DESTINATION ${SVN_REV}/bin
	LIBRARY DESTINATION ${SVN_REV}/lib
	ARCHIVE DESTINATION ${SVN_REV}/lib/static
	)

INSTALL (
	PROGRAMS ${TESTS_LIST} DESTINATION ${SVN_REV}/bin/test
	)