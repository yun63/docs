// -------------------------------------------------------------------------------------
// 
//    @filename         :  circular_list.h
// 
//    @description      :  带头节点的循环链表
// 
// -------------------------------------------------------------------------------------
//    @version          :  1.0
//    @created          :  2013年06月01日 22时08分55秒
//    @revision         :  none
//    @compiler         :  g++
// 
//    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @Company          :  
// 
// -------------------------------------------------------------------------------------

#ifndef  H_CIRCULAR_LIST_INC
#define  H_CIRCULAR_LIST_INC

#include <iostream>
#include <sstream>
#include <string>

#include "link_node.h"
#include "exceptions.h"

using namespace std;

template<class T>
class CCircularList
{
	public:
		// constructor
		CCircularList( );
		~CCircularList( );

		int size( ) const { return size_; }
		int indexof(const T &elem) const;
		void insert(int index, const T &elem);
		void erase(int index, T &elem);
		void output(ostream &out) const;

	protected:
		void CheckIndex(int index) const;

		CLinkNode<T> *head_;
		int size_;
};

template<class T>
CCircularList<T>::CCircularList( )
{
	head_ = new CLinkNode<T>( );
	head_->next_ = head_;
	size_ = 0;
}

template<class T>
CCircularList<T>::~CCircularList( )
{
	if (head_ != NULL)
	{
		CLinkNode<T> *temp = head_;
		CLinkNode<T> *p = head_->next_;

		while (p != head_)
		{
			delete temp;
			temp = p;
			p = p->next_;
		}
		delete temp;
		size_ = 0;
	}
}

template<class T>
void CCircularList<T>::CheckIndex(int index) const
{
	if (index < 0 || index >= size_)
	{
		ostringstream s;
		s << "index = " << index << " size = " << size_;
		throw CIllegalIndex(s.str( ));
	}
}

template<class T>
int CCircularList<T>::indexof(const T &elem) const
{
	// Return index of first occurrence of elem
	// Return -1 if elem not in list.
	
	// Put elem in head node
	head_->element_ = elem;

	// search the list for elem
	CLinkNode<T> *p = head_->next_;
	int index = 0;
	while (p->element_ != elem)
	{
		// move to next node
		p = p->next_;
		index++;
	}
	
	// make sure we found matching element
	if (p == head_)
	{
		index = -1;
	}
	return index;
}

template<class T>
void CCircularList<T>::insert(int index, const T &elem)
{
	// Insert elem so that its index is 'index'
	if (index < 0 || index > size_)
	{
		ostringstream s;
		s << "index = " << index << " size = " << size_;
		throw CIllegalIndex(s.str( ));
	}

	// find predecessor of new element
	CLinkNode<T> *p = head_;
	for (int i = 0; i < index; ++i)
	{
		p = p->next_;
	}

	// insert after p
	p->next_ = new CLinkNode<T>(elem, p->next_);
	size_++;
}

template<class T>
void CCircularList<T>::output(ostream &out) const
{
	for (CLinkNode<T> *p = head_->next_;
					   p != head_;
					   p = p->next_)
	{
		out << p->element_ << " -> ";
	}
}

// overload <<
template<class T>
ostream &operator << (ostream &out, const CCircularList<T> &x)
{
	x.output(out);
	return out;
}

#endif   // ----- #ifndef CIRCULAR_LIST_INC  -----
