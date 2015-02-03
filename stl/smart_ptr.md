
C++智能指针用法
====

c++的四个智能指针

* auto_ptr 

* shared_ptr 

* weak_ptr 

* unique_ptr

其中, shared_ptr, weak_ptr, unique_ptr是c++11支持, auto_ptr已经被c++废弃.

----------

## 1. 为什么要使用智能指针?

c++内存管理是件令人头疼的事情,我们new一个对象出来后可能还未执行到delete时就跳转了或者在函数中没有执行到最后的delete语句就返回了,
如果我们不在每一个可能跳转或者返回的语句前释放资源,就会造成内存泄露.智能指针可以很大程度上解决这个问题.

智能指针是一个类,当超出类的作用域时,类就会自动调用析构函数释放资源.

1.  auto_ptr(c++11废弃) [官方文档](http://www.cplusplus.com/reference/memory/auto_ptr)

智能指针可以像类的原始指针一样访问类的public成员,成员函数get()返回一个原始指针,成员函数reset()重新绑定指向的对象,
而原来的对象则会被释放.

注意,访问auto_ptr的成员函数时用".",访问指向对象的

