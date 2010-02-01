#include "GenericError.hh"

#include "ErrorCode.hh"
#include "ErrorCondition.hh"

namespace Core
{

namespace Error
{

inline bool operator!=( const ErrorCode & lhs, const ErrorCode & rhs )
{
    return !(lhs == rhs);
}

inline bool operator!=( const ErrorCondition & lhs, const ErrorCondition & rhs )
{
    return !(lhs == rhs);
}

inline bool operator==( const ErrorCode & code, const ErrorCondition & condition )
{
    return code.category().equivalent( code.value(), condition ) || condition.category().equivalent( code, condition.value() );
}

inline bool operator!=( const ErrorCode & lhs, const ErrorCondition & rhs )
{
    return !(lhs == rhs);
}

inline bool operator==( const ErrorCondition & condition, const ErrorCode & code )
{
    return condition.category().equivalent( code, condition.value() ) || code.category().equivalent( code.value(), condition );
}

inline bool operator!=( const ErrorCondition & lhs, const ErrorCode & rhs )
{
    return !(lhs == rhs);
}



//  make_* functions for errcode::errcode_t  -----------------------------//

//  explicit conversion:
inline ErrorCode makeErrorCode( Generic::error_code_t e )
{
    return ErrorCode( e, getGenericCategory() );
}

//  implicit conversion:
inline ErrorCondition makeErrorCondition( Generic::error_code_t e )
{
    return ErrorCondition( e, getGenericCategory() );
}



} // Error

}// Core
