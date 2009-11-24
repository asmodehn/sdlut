#ifndef CORE_HH
#define CORE_HH


///Main include files to load Core features needed for virtual environments applications.

#include "dbgmem.h"
#include "StaticAssert.hh"
#include "Logger.hh"
#include "Time.hh"
#include "Randomizer.hh"

#include "Functor.hh"
#include "Callback.hh"
#include "Adapter.hh"

#ifdef WK_SigCxx_FOUND
#include "sigc++.h"
#endif

#include "Distribution.hh"



#endif
