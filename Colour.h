#ifndef COLOUR_H_
#define COLOUR_H_
#include<ostream>
#include<string>

namespace colour
{
	const char NORMAL[5] = "\033[0m";

	class RGB
	{
	private:
		int r;
		int g;
		int b;
	public:
		RGB();
		RGB(const int r, const int g, const int b);
		RGB(const RGB& RGBobj);
		RGB& operator=(const RGB& RGBobj);
		~RGB();
		friend std::ostream& operator<<(std::ostream& os, const RGB& RGBobj);
	};
}

#endif // !COLOUR_H_