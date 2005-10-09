#ifndef MATH2D_HH
#define MATH2D_HH

#include <iostream>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265
#endif
#ifndef M_1_PI
#define M_1_PI (1.0 / 3.14159265)
#endif

//TODO : template !!! to be able to use int, float, etc...
class Vector2
{
	
  //global double tolerance
  static const int precision = -10;
  //MAGIC NUMBER !!! CAREFULL...
  //HAS TO BE DONE BETTER LATER...

	private :
	
  double _x,_y;
  
  public :
  //default constructor override
  Vector2(double xi = 0, double yi = 0);
  //copy constructor override
  Vector2(const Vector2 & v);
  //destructor
  ~Vector2(void);
  
  inline double x() const { return getx(); }
  inline double y() const { return gety(); }
  double getx(void) const;
  double gety(void) const;
  
  void setx(double xi);
  void sety(double yi);
  
  double operator [] (int i) const;
	double &operator [] (int i);
  
  double magnitude(void) const;
  void normalize(void);
  void reverse(void);
  
  Vector2& operator+=(const Vector2& u);
  Vector2& operator-=(const Vector2& u);
  Vector2& operator*=(double s);
  Vector2& operator/=(double s);
  
  Vector2 operator-(void);
  Vector2 operator+( const Vector2& u) const;
  Vector2 operator-( const Vector2& u) const;
  double operator*( const Vector2& v) const;

  friend Vector2 operator*(double s, const Vector2& u);
  friend Vector2 operator*(const Vector2& u, double s);
  friend Vector2 operator/(const Vector2& u, double s);
  
  bool isNull() const;
  
  friend std::ostream & operator << (std::ostream & ostr, const Vector2 & u);
  
};

inline Vector2::Vector2(double xi, double yi)
{
	_x=xi;
	_y=yi;
}

inline Vector2::Vector2(const Vector2 & v)
{
	_x=v._x;
	_y=v._y;
}

inline Vector2::~Vector2(void)
{
}

inline double Vector2::getx(void) const
{
	return _x;
}

inline double Vector2::gety(void) const
{
	return _y;
}
 
inline void Vector2::setx(double xi)
{
	_x=xi;
}

inline void Vector2::sety(double yi)
{
	_y=yi;
}

inline double Vector2::operator [] (int i) const
{
	return *(&_x + i);
}

inline double & Vector2::operator [] (int i)
{
	return *(&_x + i);
}
	

inline double Vector2::magnitude(void) const
{
	return sqrt(_x*_x+_y*_y);
}

inline  void Vector2::normalize(void)
{
	double m = magnitude();
	double tolerance = pow(10,precision);
	if ( m <= tolerance ) m = 1;
	_x /= m;
	_y /= m;
	
	if (fabs(_x) < tolerance ) _x = 0.0;
	if (fabs(_y) < tolerance ) _y = 0.0;
}

inline void Vector2::reverse(void)
{
	_x = -_x;
	_y = -_y;
}

inline Vector2& Vector2::operator+=(const Vector2& u)
{
	_x += u._x;
	_y += u._y;
	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& u)
{
	_x -= u._x;
	_y -= u._y;
	return *this;
}

inline Vector2& Vector2::operator*=(double s)
{
	_x *= s;
	_y *= s;
	return *this;
}

inline Vector2& Vector2::operator/=(double s)
{
	_x /= s;
	_y /= s;
	return *this;
}

inline Vector2 Vector2::operator-(void)
{
	return Vector2(-_x,-_y);
}

inline Vector2 Vector2::operator+( const Vector2& u ) const
{
	return Vector2( _x + u._x , _y + u._y );
}

inline Vector2 Vector2::operator-( const Vector2& u ) const
{
	return Vector2( _x - u._x , _y - u._y );
}

inline double Vector2::operator*( const Vector2& u ) const
{
	return ( _x * u._x + _y * u._y );
}

//scalar multiplication
inline Vector2 operator*(double s, const Vector2& u)
{
	return Vector2 ( u._x * s, u._y * s );
}

//scalar multiplication
inline Vector2 operator*(const Vector2& u, double s)
{
	return Vector2 ( u._x * s, u._y * s );
}

//scalar division
inline Vector2 operator/(const Vector2& u, double s)
{
	return Vector2 ( u._x / s, u._y / s );
}

inline bool Vector2::isNull() const
{
	return ( (_x == 0.0) && (_y == 0.0) );
}

inline std::ostream & operator << (std::ostream & ostr, const Vector2 & u)
{
	ostr << '(' << u._x << ',' << u._y << ')' ;
	return ostr;
}

//TODO LATER : Vector 3 with cross product, and triple scalar product.

#endif
