///-------------------------------------------------------------------------------------
///
///   @filename         :  stack.h
///
///   @description      :  This .h file includes two classes.
///   CStack class is a abstract class, defines the data type specification structure,
///   its all methods are pure virtual functions; CSqStack is derived from base class 
///   CStack.
///-------------------------------------------------------------------------------------
///   @version          :  1.0
///   @created          :  2013年06月07日 00时32分35秒
///   @revision         :  none
///   @compiler         :  g++
///
///   @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
///   @Company          :  
///
///-------------------------------------------------------------------------------------

#ifndef  H_STACK_INC
#define  H_STACK_INC

#include <sstream>
#include "exceptions.h"

using namespace std;

template<class T>
class CStack
{
	public:
		virtual ~CStack( ) { }
		virtual bool empty( ) const = 0;
		virtual int size( ) const = 0;
		virtual T &top( ) = 0;
		virtual void pop( ) = 0;
		virtual void push(const T &elem) = 0;
};

template<class T>
class CSqStack : public CStack< T >
{
	public:
		CSqStack(int initialcapacity = 10);
		~CSqStack( ) { delete []stack_; }
		bool empty( ) const { return top_ == -1; }
		int size( ) const { return top_ + 1; }
		/**
		 * @brief  &top 获取栈顶元素
		 * @return  
		 */
		T &top( );
		/**
		 * @brief  pop 出栈
		 */
		void pop( );
		/**
		 * @brief  push 入栈
		 * @param  elem
		 */
		void push(const T &elem);

	protected:
		int top_;
		int size_;
		T *stack_;
};

template<class T>
CSqStack<T>::CSqStack(int initialcapacity)
{
	if (initialcapacity < 1)
	{
		ostringstream s;
		s << "initial capacity of stack must be bigger than 0, now \
			the capacity is " << initialcapacity << endl;
		throw CIllegalParameterValue(s.str( ));
	}
	size_ = initialcapacity;
	stack_ = new T[size_];
	top_ = -1;
}

template<class T>
T &CSqStack<T>::top( ) 
{
	if (empty( ))
	{
		throw CStackEmpty( );
	}
	return stack_[top_];
}

template<class T>
void CSqStack<T>::pop( )
{
	if (empty( ))
	{
		throw CStackEmpty( );
	}
	stack_[top_--].~T( );
	size_--;
}

template<class T>
void CSqStack<T>::push(const T &elem)
{
	// add elem to stack
	if (top_ == size_)
	{
		// no space, double capacity
		T *p = new T[2 * size_];
		copy(stack_, stack_ + size_, p);
		delete []stack_;
		stack_ = p;
		size_ = size_ << 1;
	}

	// add at stack top
	stack_[++top_] = elem;
}

///===========================================================================
/// @class      :  CLinkStack
/// @description:  链式栈的声明及实现
///===========================================================================
#include "link_node.h"

template<class T>
class CLinkStack : public CStack< T >
{
	public:
		CLinkStack(int initialcapacity = 10);
		~CLinkStack( );
		/**
		 * @brief  empty 链栈判空
		 * @return  
		 */
		bool empty( ) const { return size_ == 0; }
		/**
		 * @brief  size 返回栈的长度
		 * @return  
		 */
		int size( ) const { return size_; }
		/**
		 * @brief  &top 返回栈顶元素
		 * @return  
		 */
		T &top( );
		/**
		 * @brief  pop 出栈
		 */
		void pop( );
		/**
		 * @brief  push 压栈
		 * @param  element
		 */
		void push(const T &element);

	private:
		CLinkNode<T> *top_;
		int size_;
};

template<class T>
CLinkStack<T>::CLinkStack(int initialcapacity)
{
	top_  = NULL;
	size_ = 0;
}

template<class T>
CLinkStack<T>::~CLinkStack( )
{
	while (top_ != NULL)
	{
		CLinkNode<T> *next = top_->next_;
		delete top_;
		top_ = next;
	}
}

template<class T>
T &CLinkStack<T>::top( )
{
	if (size_ == 0)
	{
		throw CStackEmpty( );
	}
	return top_->element_;
}

template<class T>
void CLinkStack<T>::pop( )
{
	if (size_ == 0)
	{
		throw CStackEmpty( );
	}
	CLinkNode<T> *next = top_->next_;
	delete top_;
	top_ = next;
	size_--;
}

template<class T>
void CLinkStack<T>::push(const T &element)
{
	top_ = new CLinkNode<T>(element, top_);
	size_++;
}

#endif   // ----- #ifndef STACK_INC  -----
