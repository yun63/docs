// -------------------------------------------------------------------------------------
// 
//    @filename         :  queque.h
// 
//    @description      :  This .h file include two classes. 
//    CQueue class is a abstract class , it defines abstract data type specification 
//    for queue data structure, all mothods are pure virtual functions;
//    CSqueue is a sequence queue, which is derived from CQueue.
//
// -------------------------------------------------------------------------------------
//    @version          :  1.0
//    @created          :  2013年06月12日 23时04分06秒
//    @revision         :  none
//    @compiler         :  g++
// 
//    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @Company          :  
// 
// -------------------------------------------------------------------------------------

#ifndef  H_QUEQUE_INC
#define  H_QUEQUE_INC

#include <sstream>
#include "exceptions.h"

using namespace std;

// -------------------------------------------------------------------------------------
//  @class      :  CSqueue
//  @description:  Base class for queue.
// -------------------------------------------------------------------------------------
template<class T>
class CQueue
{
	public:
		virtual ~CQueue( ) { }
		/**
		 * @brief  empty return true if queue is empty.
		 * @return  
		 */
		virtual bool empty( ) const = 0;
		/**
		 * @brief  size return number of elements in queue.
		 * @return  
		 */
		virtual int size( ) const = 0;
		/**
		 * @brief  &front return reference to the front element.
		 * @return  
		 */
		virtual T &front( ) = 0;
		/**
		 * @brief  &back return reference to the back element.
		 * @return  
		 */
		virtual T &back( ) = 0;
		/**
		 * @brief  pop remove the front element in the queue.
		 */
		virtual void pop( ) = 0;
		/**
		 * @brief  push add element at the back of queue.
		 */
		virtual void push(const T &elem) = 0;
};

/// ===========================================================================
///  @class      :  CQueue
///  @description:  带模版类的线性队列声明及实现，采用线性表模拟队列操作
/// ===========================================================================
template<class T>
class CSqueue : public CQueue<T>
{
	public:
		CSqueue(int initialcapacity = 10);
		~CSqueue( ) { delete []queue_; }
		/**
		 * @brief  empty 队列判空
		 * @return  
		 */
		bool empty( ) const { return front_ == rear_; }
		/**
		 * @brief  size 队列的长度
		 * @return  
		 */
		int size( ) const { return (rear_ - front_ + length_) % length_; }
		/**
		 * @brief  &front 队头元素
		 * @return  
		 */
		T &front( )
		{
			if (empty( ))
			{
				throw CSqueueEmpty( );
			}
			return queue_[(front_ + 1) % length_];
		}
		/**
		 * @brief  &back 队尾元素
		 * @return  
		 */
		T &back( )
		{
			if (empty( ))
			{
				throw CSqueueEmpty( );
			}
			return queue_[rear_];
		}
		/**
		 * @brief  pop 出队列
		 */
		void pop( )
		{
			if (empty( ))
			{
				throw CSqueueEmpty( );
			}
			front_ = (front_ + 1) % length_;
			queue_[front_].~T( );
		}
		/**
		 * @brief  push 如队列
		 * @param  elem
		 */
		void push(const T &elem);
		
	private:
		int front_;                             // 队头游标
		int rear_;                              // 队尾游标
		int length_;                            // 队列长度
		T *queue_;                              // 队列存储结构
};

template<class T>
CSqueue<T>::CSqueue(int initialcapacity)
{
	if (initialcapacity < 1)
	{
		ostringstream s;
		s << "initial capacity " << initialcapacity << " must be bigger than 0";
		throw CIllegalParameterValue(s.str( ));
	}
	length_ = initialcapacity;
	queue_ = new T[length_];
	front_ = 0;
	rear_ = 0;
}

template<class T>
void CSqueue<T>::push(const T &elem)
{
	if ((rear_ + 1) % length_ == front_)
	{
		T *q = new T[2 * length_];
		int start = (front_ + 1) % length_;

		if (start < 2)
		{
			copy(queue_ + start, queue_ + start + length_ -1, q);
		}
		else
		{
			copy(queue_ + start, queue_ + length_, q);
			copy(queue_, queue_ + rear_ + 1, q + length_ - start);
		}
		front_ = 2 * length_ - 1;
		rear_ = length_ - 2;
		length_ *= 2;
		queue_ = q;
	}

	rear_ = (rear_ + 1) % length_;
	queue_[rear_] = elem;
}

#include "link_node.h"

/// ===========================================================================
///  @class      :  CLinkQueue
///  @description:  带头结点的链式队列的实现
/// ===========================================================================
template<class T>
class CLinkQueue : public CQueue< T >
{
	public:
		CLinkQueue(int initialcapacity = 10)
		{
			front_ = rear_ = new CLinkNode<T>( ); // 生成头结点
			front_->next_ = NULL;
			size_  = 0;
		}
		~CLinkQueue( );
		/**
		 * @brief  clear 清空队列
		 */
		void clear( );
		/**
		 * @brief  empty 队列判空
		 * @return  
		 */
		bool empty( ) const { return size_ == 0; }
		/**
		 * @brief  size 返回队列长度
		 * @return  
		 */
		int size( ) const { return size_; }
		/**
		 * @brief  &front 返回队头元素引用
		 * @return  
		 */
		T &front( )
		{
			if (size_ == 0)
			{
				throw CSqueueEmpty( );
			}
			return front_->next_->element_;     // 滤过头结点
		}
		/**
		 * @brief  &back 返回队尾元素引用
		 * @return  
		 */
		T &back( )
		{
			if (size_ == 0)
			{
				throw CSqueueEmpty( );
			}
			return rear_->element_;
		}
		/**
		 * @brief  pop 出队列
		 */
		void pop( );
		/**
		 * @brief  push 如队列
		 * @param  
		 */
		void push(const T &);

	private:
		CLinkNode<T> *front_;                   // 队头指针
		CLinkNode<T> *rear_;                    // 队尾指针 
		int size_;
};

template<class T>
CLinkQueue<T>::~CLinkQueue( )
{
	while (front_ != NULL)
	{
		rear_ = front_->next_;
		delete front_;
		front_ = rear_;
	}
}

template<class T>
void CLinkQueue<T>::clear( )
{
	CLinkNode<T> *p, *q;
	p = front_->next_;
	rear_ = front_;
	while (p)
	{
		q = p;
		p = q->next_;
		delete q;
	}
}

template<class T>
void CLinkQueue<T>::pop( )
{
	if (front_->next_ == NULL)
	{
		throw CSqueueEmpty( );
	}

	CLinkNode<T> *p = front_->next_;
	delete front_;
	front_ = p;
	size_--;
}

template<class T>
void CLinkQueue<T>::push(const T &elem)
{
	CLinkNode<T> *p = new CLinkNode<T>(elem, NULL);

	// 添加新结点到队尾
	rear_->next_ = p;
	rear_ = p;
	++size_;
}

#endif   // ----- #ifndef QUEQUE_INC  -----
