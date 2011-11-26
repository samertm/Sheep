#include "point.h"

template<class T>
point<T>::point(void)
{
	x = y = 0;
}

template<class T>
point<T>::point(T& x, T& y)
{
	point::x = x;
	point::y = y;
}

template<class T>
point<T>::~point(void)
{
}
