# BetterConsole

## 类型说明

1.`MultiSelectList(const char* elements[], const int items, const int max = 100, const colour::RGB& rgb = colour::RGB(0, 153, 76));`

-创建多选列表对象

elements: 列表内容

items: 列表长度

max: 最大可选中的值

rgb: 前景色

`MultiSelectList.getSelected()`

-获取选中的元素

return: vector<int> 选中的元素索引

2.`RadioList(const char* elements[], const int items, const colour::RGB rgb = colour::RGB(0, 153, 76));`

-创建单选列表对象

elements: 列表内容

items: 列表长度

rgb: 前景色

`RadioList.getSelected()`

-获取选中的元素

return: int 选中的元素索引

## 其他

视频展示：https://www.bilibili.com/video/BV1B44y1F7uV/
希望能得到大佬指点，以及编写文档的技巧，方法，结构
