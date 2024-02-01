#include"BetterConsole.h"
#include<iostream>
#include<conio.h>
#include<string>
#include"Keycode.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include<vector>
#include"Colour.h"
#include<io.h>
#include<fcntl.h>

void gotoxy(short x, short y);

// 单个元素
bc::Element::Element() : string("Null")
{
	//std::cout << "执行Element构造函数" << std::endl;
	isChecked = false;
}

bc::Element::Element(const Element& el) : string(el.string)
{
	isChecked = el.isChecked;
}

bc::Element::Element(const std::string text) : string(text)
{
	isChecked = false;
}

bc::Element::~Element()
{
	//std::cout << "执行Element析构函数" << std::endl;
}

void bc::Element::setString(const std::string text)
{
	string = text;
}

void bc::Element::check()
{
	isChecked = !isChecked;
}

bool bc::Element::getStatus()
{
	return isChecked;
}

bc::Element& bc::Element::operator=(const bc::Element& el)
{
	string = el.string;
	isChecked = el.isChecked;
	return *this;
}

std::ostream& bc::operator<<(std::ostream& os, const bc::Element& el)
{
	os << el.string;
	return os;
}

// 多项选择列表
bc::MultiSelectList::MultiSelectList()
{
	_elements = new bc::Element[3];
	_elements[0].setString("opt1");
	_elements[1].setString("opt2");
	_elements[2].setString("opt3");

	_fgColour = colour::RGB{ 0, 153, 76 };
	_point = 0;
	_max = 3;
	_items = 3;
}

bc::MultiSelectList::MultiSelectList(const MultiSelectList& list)
{
	_elements = new Element[list._items];
	for (int item = 0; item < list._items; item++)
	{
		_elements[item] = list._elements[item];
	}

	_fgColour = list._fgColour;
	_point = list._point;
	_max = list._max;
	_items = list._items;
}

bc::MultiSelectList::MultiSelectList(const char* elements[], const int items, const int max, const colour::RGB& rgb)
{
	_elements = new Element[items];
	for (int item = 0; item < items; item++)
	{
		_elements[item].setString(elements[item]);
		//std::cout << "加载选项：" << elements[item] << std::endl;
	}

	_fgColour = rgb;
	_point = 0;
	_items = items;
	_max = max;
}

bc::MultiSelectList& bc::MultiSelectList::operator=(const MultiSelectList& list)
{
	delete[] _elements;
	_elements = new Element[list._items];

	for (int item = 0; item < list._items; item++)
	{
		_elements[item] = list._elements[item];
	}

	_fgColour = list._fgColour;
	_point = list._point;
	_max = list._max;
	_items = list._items;
	return *this;
}

void bc::MultiSelectList::addPoint(int n)
{
	if ((_point + n >= 0) && (_point + n < _items))
	{
		_point += n;
	}
}

std::ostream& bc::operator<< (std::ostream& os, bc::MultiSelectList& list)
{
	//std::cout << "获取键值" << std::endl;

	short x, y;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;
	}
	else
	{
		std::cout << "读取错误" << std::endl;
		return os;
	}

	list.showList();

	int ch, checked;

	checked = 0;

	while (true)
	{
		if (_kbhit())
		{
			ch = _getch(); // 按键

			if (ch == 224)
			{
				switch (_getch())
				{
				case KEY_DOWN: 
					list.addPoint(1);
					//std::cout << "point:" << list._point << std::endl;
					gotoxy(x, y);
					list.showList();
					break;

				case KEY_UP: 
					list.addPoint(-1);
					//std::cout << "point:" << list._point << std::endl;
					gotoxy(x, y);
					list.showList();
					break;
				}
			}
			else if (ch == KEY_SPACE)
			{
				if (checked < list._max && !list._elements[list._point].getStatus())
				{
					list._elements[list._point].check();
					checked++;
					//std::cout << "check:" << list._point << "\tchecked:" << checked << std::endl;
					gotoxy(x, y);
					list.showList();
				}
				else if (list._elements[list._point].getStatus()) // 特殊情况，取消选中
				{
					list._elements[list._point].check();
					checked--;
					//std::cout << "check:" << list._point << "\tchecked:" << checked << std::endl;
					gotoxy(x, y);
					list.showList();
				}
			}
			else if (ch == KEY_ENTER)
			{
				break;
			}
		}
	}
	return os;
}

std::vector<int> bc::MultiSelectList::getSelected() const
{
	std::vector<int> result;
	for (int count = 0; count < _items; count++)
	{
		if (_elements[count].getStatus())
		{
			result.push_back(count);
		}
	}
	return result;
}

bc::MultiSelectList::~MultiSelectList()
{
	//std::cout << "执行析构函数" << std::endl;
	delete[] _elements;
}

void bc::MultiSelectList::showList() const
{
	std::cout << std::endl;

	for (int count = 0; count < _items; count++)
	{
		if (count == _point)
		{
			std::cout << "[  ";
		}
		else
		{
			std::cout << "   ";
		}

		if (_elements[count].getStatus())
		{
			std::cout << _fgColour;
			// https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/reference/setmode?view=msvc-170
			int mode = _setmode(_fileno(stdout), _O_U16TEXT);
			std::wcout << checked;
			mode = _setmode(_fileno(stdout), mode);
			std::cout << "  " << _elements[count];
		}
		else
		{
			int mode = _setmode(_fileno(stdout), _O_U16TEXT);
			std::wcout << unchecked;
			mode = _setmode(_fileno(stdout), mode);
			std::cout << "  " << _elements[count];
		}

		std::cout << colour::NORMAL;

		std::cout << std::endl;
	}
}

bc::RadioList::RadioList()
{
	_elements = new bc::Element[3];
	_elements[0].setString("opt1");
	_elements[1].setString("opt2");
	_elements[2].setString("opt3");

	_fgColour = colour::RGB{ 0, 153, 76 };
	_point = 0;
	_items = 3;
}

bc::RadioList::RadioList(const RadioList& list)
{
	_elements = new Element[list._items];
	for (int item = 0; item < list._items; item++)
	{
		_elements[item] = list._elements[item];
	}

	_fgColour = list._fgColour;
	_point = list._point;
	_items = list._items;
}

bc::RadioList::RadioList(const char* elements[], const int items, const colour::RGB rgb)
{
	_elements = new Element[items];
	for (int item = 0; item < items; item++)
	{
		_elements[item].setString(elements[item]);
		//std::cout << "加载选项：" << elements[item] << std::endl;
	}

	_fgColour = rgb;
	_point = 0;
	_items = items;
}

bc::RadioList& bc::RadioList::operator=(const bc::RadioList& list)
{
	delete[] _elements;
	_elements = new Element[list._items];

	for (int item = 0; item < list._items; item++)
	{
		_elements[item] = list._elements[item];
	}

	_fgColour = list._fgColour;
	_point = list._point;
	_items = list._items;
	return *this;
}

std::ostream& bc::operator<< (std::ostream& os, bc::RadioList& list)
{
	//std::cout << "获取键值" << std::endl;

	short x, y;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;
	}
	else
	{
		std::cout << "读取错误" << std::endl;
		return os;
	}

	list.showList();

	int ch;

	while (true)
	{
		if (_kbhit())
		{
			ch = _getch(); // 按键

			if (ch == 224)
			{
				switch (_getch())
				{
				case KEY_DOWN:
					list.addPoint(1);
					//std::cout << "point:" << list._point << std::endl;
					gotoxy(x, y);
					list.showList();
					break;

				case KEY_UP:
					list.addPoint(-1);
					//std::cout << "point:" << list._point << std::endl;
					gotoxy(x, y);
					list.showList();
					break;
				}
			}
			else if (ch == KEY_ENTER)
			{
				break;
			}
		}
	}
	return os;
}

void bc::RadioList::addPoint(int n)
{
	if ((_point + n >= 0) && (_point + n < _items))
	{
		_point += n;
	}
}

void bc::RadioList::showList() const
{
	std::cout << std::endl;

	for (int count = 0; count < _items; count++)
	{
		if (count == _point)
		{
			std::cout << "[  " << _fgColour << _elements[count] << colour::NORMAL;
		}
		else
		{
			std::cout << "   " << _elements[count];
		}

		std::cout << std::endl;
	}
}

int bc::RadioList::getSelected() const
{
	return _point;
}

bc::RadioList::~RadioList()
{
	//std::cout << "执行析构函数" << std::endl;
	delete[] _elements;
}

void gotoxy(short x, short y) 
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}