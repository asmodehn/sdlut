/* *
 *  Copyright (c) 2009, Asmodehn's Corp.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *      - Redistributions of source code must retain the above copyright notice,
 * 	    this list of conditions and the following disclaimer.
 *      - Redistributions in binary form must reproduce the above copyright
 * 		notice, this list of conditions and the following disclaimer in the
 * 	    documentation and/or other materials provided with the distribution.
 *      - either the name of the Asmodehn's Corp. nor the names of its
 * 	    contributors may be used to endorse or promote products derived
 * 	    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 *  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *  THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef CONFIG_HH
#define CONFIG_HH

//If we are built using WkCMake, we can use WkPlatform Detection

#ifdef WK_BUILD
# include "WkPlatform_Core.h"
# if defined ( WK_Core_PLATFORM_IS_WIN32 )
#  define CORE_PLATFORM_WIN32
# elif defined ( WK_Core_PLATFORM_POSIX )
#  define CORE_PLATFORM_POSIX
# endif
# define CORE_API WK_Core_API
# define CORE_LOCAL WK_Core_LOCAL

// TODO
/*
#else

//We have to do our own platform checks

//Platform type detection
#if defined (__MINGW32__) || defined (_MSC_VER) || defined (_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__CYGWIN__)
#define CORE_PLATFORM_WIN32
#elif defined ( _POSIX_SOURCE ) || defined ( _POSIX_C_SOURCE )
#define CORE_PLATFORM_POSIX
#endif

//adjusting declspec values

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
#define CORE_HELPER_DLL_IMPORT __declspec(dllimport)
#define CORE_HELPER_DLL_EXPORT __declspec(dllexport)
#define CORE_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define CORE_HELPER_DLL_IMPORT __attribute__ ((visibility("default")))
#define CORE_HELPER_DLL_EXPORT __attribute__ ((visibility("default")))
#define CORE_HELPER_DLL_LOCAL  __attribute__ ((visibility("hidden")))
#else
#define CORE_HELPER_DLL_IMPORT
#define CORE_HELPER_DLL_EXPORT
#define CORE_HELPER_DLL_LOCAL
#endif
#endif

#ifdef CORE_BUILD // Core library building
#define CORE_API CORE_HELPER_DLL_EXPORT
#define CORE_LOCAL CORE_HELPER_DLL_LOCAL
#else // Core library using
#define CORE_API CORE_HELPER_DLL_IMPORT
#define CORE_LOCAL CORE_HELPER_DLL_LOCAL
#endif

#ifndef NULL
#define NULL 0
#endif
*/

#endif // WK_BUILD







#endif // CONFIG _HH
