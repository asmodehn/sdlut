#linking SDLWrap
LINK_LIBRARIES(bin/SDLWrap)

ADD_EXECUTABLE(test/checkkeys test/checkkeys.cc)
ADD_DEPENDENCIES(test/checkkeys SDLWrap)