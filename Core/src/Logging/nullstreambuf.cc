#include "Core/Logging/nullstreambuf.hh"

namespace Core
{
namespace stdext
{

template <class _CharT, class _Traits>
basic_nullstreambuf<_CharT, _Traits>::basic_nullstreambuf()
: std::basic_streambuf<_CharT, _Traits>()
{
}

template <class _CharT, class _Traits>
basic_nullstreambuf<_CharT, _Traits>::~basic_nullstreambuf()
{
}


template <class _CharT, class _Traits>
void basic_nullstreambuf<_CharT, _Traits>::imbue(const std::locale& __loc)
{
  }


}
}

