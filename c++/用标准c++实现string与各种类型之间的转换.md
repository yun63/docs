用标准c++实现string与各种类型之间的转换
========================================

<sstream>头文件定义了三种类：istringstream、ostringstream和stringstream，分别用来进行流的输入、输出和输入输出操作。另外，每个类都有一个对应的宽字符集版本。

## 1 string到int的转换

```
std::stringstream stream;
string result = "10000";
int n = 0;
stream << result;
stream >> n; // n等于10000
```

## 2 int到string的转换

```
string result;
int n = 12345;
std::stringstream stream;
stream << n;
stream >> result; // result等于"12345"
```

**如果你打算在多次转换中使用同一个stringstream对象，记住在每次转换前要是用clear()方法，
在多次转换中使用同一个stringstream对象最大的好处在于效率，stringstream对象的构造和析构函数通常是非常消耗cpu时间的。单单使用clear并不能清除stringstream对象的内容，仅仅是清除了该对象的状态，
要重复使用同一个stringstream对象，需要使用str()重新初始化该对象**

