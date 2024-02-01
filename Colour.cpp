#include"Colour.h"
#include<ostream>

colour::RGB::RGB() : r(0), g(0), b(0)
{

}

colour::RGB::RGB(const int r, const int g, const int b) : r(r), g(g), b(b)
{

}

colour::RGB::~RGB()
{

}

colour::RGB& colour::RGB::operator=(const colour::RGB& RGBobj)
{
	r = RGBobj.r;
	g = RGBobj.g;
	b = RGBobj.b;
	return *this;
}

colour::RGB::RGB(const colour::RGB& RGBobj) : r(RGBobj.r), g(RGBobj.r), b(RGBobj.r)
{

}

std::ostream& colour::operator<<(std::ostream& os, const colour::RGB& RGBobj)
{
	os << "\033[38;2;" << RGBobj.r << ";" << RGBobj.g << ";" << RGBobj.b << "m";
	return os;
}