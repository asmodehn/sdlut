/*
Made by XorfacX
*/
#ifndef GCN_SDLutDepends_HPP
#define GCN_SDLutDepends_HPP

//Include the main SDLut header
#include "SDL.hh"

using namespace SDLut;
using namespace RAGE;


#if defined(_MSC_VER)

typedef signed __int8		int8_t;
typedef unsigned __int8		uint8_t;
typedef signed __int16		int16_t;
typedef unsigned __int16	uint16_t;
typedef signed __int32		int32_t;
typedef unsigned __int32	uint32_t;
typedef signed __int64		int64_t;
typedef unsigned __int64	uint64_t;

typedef int8_t		Sint8;
typedef uint8_t		Uint8;
typedef int16_t		Sint16;
typedef uint16_t	Uint16;
typedef int32_t		Sint32;
typedef uint32_t	Uint32;

#endif

#endif
