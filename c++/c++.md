
C++编程实践
===========

### 指针运算符重载

当对某个类实施operator->,而这个类并非原生指针的时候,编译器会从这个类中找出用户自定义的operator->,并实施,编译器会继续对这个operator->
返回的结果再次实施operator->操作,直到找到一个原生指针为止.

这种机制导致了一个特有的技术: 前调用和后调用

```
class CallDoSomething
{
public:
    void DoCall()
    {
        TRACE("DoCall\n");
    }
};

template<class T>
class CallInMutiThread
{
    class LockProxy
    {
    public:
        LockProxy(T *pT) : m_pT(pT)
        {
            TRACE("Lock\n");
        }
        ~LockProxy()
        {
            TRACE("UnLock\n");
        }
        T *operator->() 
        {
            return m_pT;
        }
    private:
        T *m_pT;
    };
public:
    CallInMutiThread(T *pT) : m_pT(pT)
    {
    }
    LockProxy operator->()
    {
        return LockProxy(m_pT);
    }

private:
    T *m_pT;
};
```

调用过程如下:

```
CallDoSomething DoSomething;
CallInMutiThread<CallDoSomething> MutiThread(&DoSomething);
MutiThread->DoCall();
```

调用结果如下:

Lock
DoCall
UnLock


### 模板

1. 模板函数

```
template<typename T>
inline T const &max(T const &a, T const &b)
{
    return a < b ? b : a;
}
```

调用形式:

+ 通过调用的参数来识别模板的各参数类型

    max(4, 4.2); // ok, 但是模板的第一个参数类型定义了返回类型

+ 明确指定参数类型

    max<int>(4, 4.2); // ok

2. 重载模板函数

```
inline const &max(int const &a, int const &b)
{
    return a < b ? b : a;
}

template<typename T>
inline T const &max(T const &a, T const &b)
{
    return a < b ? b : a;
}

template<typename T>
inline T const &max(T const &a, T const &b, T const &c)
{
    return max(max(a, b), c);
}
```

3. 模板类

具有缺省参数的模板定义:

```
template<typename T, typename Alloc=alloc>
class class-name
{
    ...
};
```

模板设计思维方法:

* 声明一个函数但并不实现

```
class TestDeclare
{
    public:
        TestDeclare();
};
```

TestDeclare declare; // error

* 声明一个函数而不实现可能是为了模板函数的泛化

    泛化:
    ```
    template<typename T>
    T fun();
    ```

    特化:
    ```
    template<>
    int fun() { return 10; }
    ```

* 声明一个类而不实现

```
template<typename T>
class Test; // 泛化只声明

template<>
class Test<int> // 特化进行实现
{
};

Test<char> test; // error
Test<int> test;  // ok
```

-----------------------

4. 模板设计基本方法

+ 编译器断言

```
template<class T, class U>
{
    typedef char small;
    class big { char dummy[2] };
    static small test(U);
    static big test(...);
    static T markT();

public:
    enum{value = sizeof(test(markT())) == sizeof(small)};
};
```

+ 模板特化

```
template<typename T, typename Y>
struct Test
{
    Test() { cout << "T, Y" << endl; }
};

template<typename T>
struct Test<T *, T *>
{
    Test() { cout << "T *, T*" << endl; }
};
```

+ 常数映射类

```
template<int v>
struct Test
{
    enum{value = v};
};
```

+ 类映射类

```
template<typename T>
struct Test
{
    typedef T OriginalType;
};
```



### STL标准模板库

#### 容器

1. 顺序容器

vector, list, deque, stack(没有迭代器), queue(没有迭代器), 即stack, queue不允许遍历行为

2. 关联容器

set(标准),map(标准), hash_table, RB-tree

3. 通用算法

begin(), end(), size(), empty(), erase(iterator __pos), clear()

#### 迭代器

迭代器的基本算法

1. 能够进行+, -, ++, --, +=, -=, ==, !=等运算
2. 一种智能指针,实现operator *, operator->的重载
3. 迭代器前闭后开区间[first, last)

迭代器的类型

1. 单向迭代器
2. 可逆迭代器
3. 随机迭代器

#### 算法

1. 数值运算

power, itoa, accumulate

2. 基本运算

fill, fill_n, swap, max, min, iter_sawp, copy

3. 集合运算

set_union, set_interseion, set_diffrence

4. 数据整理

count, count_if, find, find_if, for_each, merge, sort, upper, search, search_n

#### 仿函数


