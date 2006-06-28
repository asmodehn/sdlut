CMAKE_MINIMUM_REQUIRED ( VERSION 2.4)

#Project Definition
PROJECT(Math)

INCLUDE(../RageCommon.cmake)

#
# Defining what needs to be built
#

RAGE_BUILD(${PROJECT_NAME} LIBRARY)

#
# Defining a set of Tests
#

ADD_SUBDIRECTORY(test)

RAGE_INSTALL(${PROJECT_NAME})
