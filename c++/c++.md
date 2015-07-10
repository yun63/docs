
C++编程实践
===========

1. 指针运算符重载

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


