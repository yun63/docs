// #####################################################################################
// 
//    @filename         :  link_list.h
// 
//    @description      :  define all operations of link list
//
//    1	derives from abstract class CLinearList just to make sure all methods of the ADT 
//    are implemented.
// 
//######################################################################################
//    @version          :  1.0
//    @created          :  05/26/13 23:16:58
//    @revision         :  none
//    @compiler         :  g++
// 
//    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @Company          :  
// 
// #####################################################################################


#ifndef  H_LINK_LIST_INC
#define  H_LINK_LIST_INC

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

#include "linear_list.h"
#include "link_node.h"
#include "exceptions.h"

using namespace std;

template<class T>
class CLinkList : public CLinearList<T>
{
	public:
		// constructor, copy constructor and destructor
		CLinkList(int initialize_capacity = 10);
		CLinkList(const CLinkList<T> &);
		~CLinkList( );

		bool empty( ) const { return size_ == 0; }
		int size( ) const { return size_; }
		T &get(int index) const;
		int indexof(const T &elem) const;
		void erase(int index);
		void insert(int index, const T &elem);
		void output(ostream &out) const;
		void Reverse( );
		
		void BinSort(int range);
		void BinSort(int range, int (*value)(T &x));

		// iterators to start and end of link list
		class iterator;
		iterator begin( ) { return iterator(head_->next_); }
		iterator end( ) { return iterator(NULL); }

		// iterator for CLinkList
		class iterator
		{
			public:
				// typedefs required by C++ for a forward iterator
				typedef forward_iterator_tag iterator_category;
				typedef T value_type;
				typedef ptrdiff_t difference_type;
				typedef T *pointer;
				typedef T &reference;

				// constructor
				iterator(CLinkNode<T> *node = NULL) { node_ = node; }
				
				// dereferencing operations
				T &operator *() const { return node_->element_; }
				T *operator ->() const { return &node_->element_; }

				// increment
				iterator &operator ++() // preincrement
				{
					node_ = node_->next_;
					return *this;
				}
				iterator operator ++(int) // postincrement
				{
					iterator old = *this;
					node_ = node_->next_;
					return old;
				}

				// equality testing
				bool operator != (const iterator right) const
				{
					return node_ != right.node_;
				}
				bool operator == (const iterator right) const
				{
					return node_ == right.node_;
				}

			protected:
				CLinkNode<T> *node_;
		};

	protected:
		void CheckIndex(int index) const;

		CLinkNode<T> *head_;                    // pointer to first node in linklist
		int size_;                              // number of elements in linklist
};

template<class T>
CLinkList<T>::CLinkList(int initialize_capacity)
{
	if (initialize_capacity < 1)
	{
		ostringstream s;
		s << "Initial Capacity = " << initialize_capacity << " must be bigger than 0.";
		throw CIllegalParameterValue(s.str( ));
	}

	head_ = new CLinkNode<T>( );                // linklist with head node
	head_->next_ = NULL;
	size_ = 0;
}

template<class T>
CLinkList<T>::CLinkList(const CLinkList<T> &list)
{
	size_ = list.size( );
	if (size_ == 0)
	{
		head_->next_ = NULL;
		return;
	}

	CLinkNode<T> *srcnode = list.head_;         // node in the list to copy from
	head_ = new CLinkNode<T>( );
	CLinkNode<T> *targetnode = head_;
	T value;
	while (srcnode->next_ != NULL)
	{
		// copy elements		
		value = srcnode->next_->element_;
		targetnode->next_ = new CLinkNode<T>(value);
		targetnode = targetnode->next_;
		srcnode = srcnode->next_;
	}
}

template<class T>
CLinkList<T>::~CLinkList( )
{
	while (head_->next_ != NULL)
	{
		CLinkNode<T> *nextnode = head_->next_;
		head_->next_ = nextnode->next_;
		delete nextnode;
	}
}

template<class T>
void CLinkList<T>::CheckIndex(int index) const
{
	if (index < 0 || index >= size_)
	{
		ostringstream s;
		s << "index = " << index << " size = " << size_;
//		throw CIllegalIndex(s.str( ));
	}
}

template<class T>
T &CLinkList<T>::get(int index) const
{
	// return element whose index is 'index'
	CheckIndex(index);

	// nove to desired node
	CLinkNode<T> *current = head_->next_;
	for (int i = 0; i < index && current; ++i)
	{
		current = current->next_;
	}
	return current->element_;
}

template<class T>
int CLinkList<T>::indexof(const T &elem) const
{
	// return index of first occurence of elem
	// return -1 if the elem not exists in list
	//
	CLinkNode<T> *current = head_->next_;
	int index = 0;

	while (current != NULL)
	{
		if (current->element_ == elem)
		{
			return index;
		}
		current = current->next_;
		++index;
	}
	return -1;
}

template<class T>
void CLinkList<T>::erase(int index)
{
	// delete the element whose index is 'index'
	CheckIndex(index);

	// valid index, locate node with element ot delete
	CLinkNode<T> *deletenode = NULL;
	CLinkNode<T> *p = head_;
	int i = 0;
	
	while (p->next_ && i < index)
	{
		p = p->next_;
		i++;
	}
	if (!p->next_ || i > index)
	{
		return;
	}
	deletenode = p->next_;
	p->next_ = deletenode->next_;
	delete deletenode;
	deletenode = NULL;
	size_--;
}

template<class T>
void CLinkList<T>::insert(int index, const T &elem)
{
	// insert elem so that its index is 'index'
	if (index < 0 || index > size_)
	{
		// invalid index
		ostringstream s;
		s << "index = " << index << " size = " << size_;
		throw CIllegalIndex(s.str( ));
	}

	CLinkNode<T> *p = head_;
	for (int i = 0; p && i < index; ++i)
	{
		p = p->next_;
	}
	// insert after p
	CLinkNode<T> *s = new CLinkNode<T>(elem);
	s->next_ = p->next_;
	p->next_ = s;
	++size_;
}

template<class T>
void CLinkList<T>::output(ostream &out) const
{
	// put the list into the stream out.
	for (CLinkNode<T> *p = head_->next_;
					   p != NULL;
					   p = p->next_)
	{
		out << p->element_ << "	";
	}
}

template<class T>
void CLinkList<T>::Reverse( )
{
	CLinkNode<T> *pre = NULL;
	CLinkNode<T> *cur = head_->next_;
	
	while (cur != NULL)
	{
		CLinkNode<T> *post = cur->next_;
		if (post == NULL)
		{
			head_->next_ = cur;
			cur->next_ = pre;
			return;
		}
		cur->next_ = pre;
		pre = cur;
		cur = post;
	}
	head_->next_ = pre;
}

template<class T>
void CLinkList<T>::BinSort(int range)
{// 按分数排序
	assert(range > 0);

	int b; // 箱子索引号
	CLinkNode<T> **bottom, **top;
	// 初始化箱子
	bottom = new CLinkNode<T> *[range + 1];
	top = new CLinkNode<T> *[range + 1];
	for (b = 0; b <= range; ++b)
	{
		bottom[b] = 0;
	}
	// 把结点分配到对应的箱子中
	for (CLinkNode<T> *p = head_->next_; p != NULL; p = p->next_)
	{
		b = p->element_;
		if (bottom[b] == NULL)
		{
			bottom[b] = top[b] = p;
		}
		else
		{
			top[b]->next_ = p;
			top[b] = p;
		}
	}
	// 收集箱子形成排序链表
	CLinkNode<T> *y = NULL;
	for (b = 0; b <= range; ++b)
	{
		if (bottom[b] != NULL)
		{
			if (y == NULL) // 第一个非空箱子
			{
				head_->next_ = bottom[b];
			}
			else
			{
				y->next_ = bottom[b];
			}
			y = top[b];
		}
	}
	if (y != NULL)
	{
		y->next_ = NULL;
	}

	delete [ ]bottom;
	delete [ ]top;
}

template<class T>
void CLinkList<T>::BinSort(int range, int(*value)(T &x))
{
	assert(range > 0);

	int b; // 箱子索引号
	CLinkNode<T> **bottom, **top;
	// 初始化箱子
	bottom = new CLinkNode<T> *[range + 1];
	top = new CLinkNode<T> *[range + 1];
	for (b = 0; b <= range; ++b)
	{
		bottom[b] = 0;
	}
	// 把结点分配到对应的箱子中
	for (CLinkNode<T> *p = head_->next_; p != NULL; p = p->next_)
	{
		b = value(p->element_);
		if (bottom[b] == NULL)
		{
			bottom[b] = top[b] = p;
		}
		else
		{
			top[b]->next_ = p;
			top[b] = p;
		}
	}
	// 收集箱子形成排序链表
	CLinkNode<T> *y = NULL;
	for (b = 0; b <= range; ++b)
	{
		if (bottom[b] != NULL)
		{
			if (y == NULL) // 第一个非空箱子
			{
				head_->next_ = bottom[b];
			}
			else
			{
				y->next_ = bottom[b];
			}
			y = top[b];
		}
	}
	if (y != NULL)
	{
		y->next_ = NULL;
	}

	delete [ ]bottom;
	delete [ ]top;

}

// overload <<
template<class T>
ostream &operator << (ostream &out, const CLinkList<T> &x)
{
	x.output(out);
	return out;
}

#endif   // ----- #ifndef LINK_LIST_INC  -----
