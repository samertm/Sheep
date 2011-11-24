#pragma once
template<class T>
class point
{
public:
	point(void);
	point(T&, T&);
	~point(void);
	T x, y;
};

