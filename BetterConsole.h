#ifndef BETTERCONSOLE_H_
#define BETTERCONSOLE_H_
#include<ostream>
#include<string>
#include<vector>
#include"Keycode.h"
#include"Colour.h"

namespace bc
{
	const wchar_t unchecked = L'○';
	const wchar_t checked = L'●';

	class Element // 列表类的基本单位
	{
	private:
		std::string string;
		bool isChecked; // 标识是否被选中
	public:
		Element();
		Element(const Element& el);
		Element(const std::string text);
		Element& operator=(const Element& el);
		friend std::ostream& operator<<(std::ostream& os, const Element& el);
		~Element();

		void check(); // 自动取反
		bool getStatus();
		void setString(const std::string text);
	};

	class MultiSelectList // 多选列表
	{
	private:
		Element* _elements; // 列表内的元素
		colour::RGB _fgColour; // 前景色
		int _max; // 最大可选中的数量
		int _items; // 元素数量
		int _point; // 指针，表示当前所在的元素
	public:
		MultiSelectList();
		MultiSelectList(const MultiSelectList& list);
		MultiSelectList(const char* elements[], const int items, const int max = 100, const colour::RGB& rgb = colour::RGB(0, 153, 76));
		MultiSelectList& operator=(const MultiSelectList& list);
		friend std::ostream& operator<< (std::ostream& os, MultiSelectList& list);
		~MultiSelectList();

		void addPoint(int n);
		void showList() const;
		std::vector<int> getSelected() const;
	};

	class RadioList // 单选列表
	{
	private:
		Element* _elements; // 列表内的元素
		colour::RGB _fgColour;//前景色
		int _items; // 元素数量
		int _point; // 指针，表示当前所在的元素
	public:
		RadioList();
		RadioList(const RadioList& list);
		RadioList(const char* elements[], const int items, const colour::RGB rgb = colour::RGB(0, 153, 76));
		RadioList& operator=(const RadioList& list);
		friend std::ostream& operator<< (std::ostream& os, RadioList& list);
		~RadioList();

		void addPoint(int n);
		void showList() const;
		int getSelected() const;
	};
}

#endif // !BETTERCONSOLE_H_

