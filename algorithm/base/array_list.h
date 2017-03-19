// -------------------------------------------------------------------------------------
// 
//    @filename         :  array_list.h
// 
//    @description      :  array implementation of a linear list derives from
//
//    abstract class CLinearList just to make sure all methods of the ADT are
//
//    implemented
//
//    Use STL algorithms to simplify code
// 
// -------------------------------------------------------------------------------------
//    @version          :  1.0
//    @created          :  2013年06月07日 01时01分18秒
//    @revision         :  none
//    @compiler         :  g++
// 
//    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @Company          :  
// 
// -------------------------------------------------------------------------------------


#ifndef  H_ARRAY_LIST_INC
#define  H_ARRAY_LIST_INC

#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

#include "linear_list.h"
#include "exceptions.h"

template<class T>
void ChangeLength1D(T *&a, int oldlen, int newlen)
{
	if (newlen < 0) 
	{ 
		throw CIllegalParameterValue("new length must be bigger than 0");
	}

	T *p = new T[newlen];
	int number = min(oldlen, newlen);
	copy(a, a + number, p);
	delete []a;
	a = p;
}

template<class T>
class CArrayList : public CLinearList<T>
{
	public:
		CArrayList(int initcapacity = 10);
		CArrayList(const CArrayList<T> &);
		~CArrayList( ) { delete [] elements_; }

		/**
		 * @brief  empty 
		 * @return  
		 */
		bool empty( ) const { return size_ == 0; }
		/**
		 * @brief  size 
		 * @return  
		 */
		int size ( ) const { return size_; }
		/**
		 * @brief  get 
		 * @param  index
		 * @return  
		 */
		T &get(int index) const;
		/**
		 * @brief  indexof 
		 * @param  elem
		 * @return  
		 */
		int indexof(const T &elem) const;
		/**
		 * @brief  erase 
		 * @param  index
		 */
		void erase(int index);
		/**
		 * @brief  insert 
		 * @param  index
		 * @param  elem
		 */
		void insert(int index, const T &elem);
		/**
		 * @brief  output 
		 * @param  out
		 */
		void output(ostream &out) const;

		int capacity( ) const { return length_; }

		// iterators to start and end of list
		class iterator;
		iterator begin( ) { return iterator(elements_); }
		iterator end( ) { return iterator(elements_ + size_); }

		// iterator for CArrayList
		class iterator
		{
			public:
				typedef bidirectional_iterator_tag iterator_category;
				typedef T value_type;
				typedef ptrdiff_t difference_type;
				typedef T *pointer;
				typedef T &reference;

				iterator(T *it = 0) { iter_ = it; }
				T &operator *( ) const { return *iter_; }
				T *operator ->( ) const { return &*iter_; }

				/**
				 * @brief  ++() preincrement
				 * @return  
				 */
				iterator &operator ++( )
				{
					++iter_;
					return *this;
				}
				/**
				 * @brief  ++(int) postincrement
				 * @param  int
				 * @return  
				 */
				iterator operator ++(int)
				{
					iterator old = *this;
					++iter_;
					return old;
				}
				iterator &operator --( ) 
				{
					--iter_;
					return *this;
				}
				iterator operator --(int)
				{
					iterator old = *this;
					--iter_;
					return old;
				}

				bool operator != (const iterator right) const
				{
					return iter_ != right.iter_;
				}
				bool operator == (const iterator right) const
				{
					return iter_ == right.iter_;
				}

			protected:
				T *iter_;
		};  // end of iterator class
	protected:
		void CheckIndex(int index) const;

		T *elements_;                           // 1D array to hold list elements
		int length_;                            // capacity of the 1D array
		int size_;                              // number of elements in list
};

template<class T>
CArrayList<T>::CArrayList(int initcapacity)
{
	if (initcapacity < 1)
	{
		ostringstream s;
		s << "initial capacity : " << initcapacity << " must be bigger than 0";
		throw CIllegalParameterValue(s.str( ));
	}
	length_ = initcapacity;
	elements_ = new T[length_];
	size_ = 0;
}

template<class T>
CArrayList<T>::CArrayList(const CArrayList<T> &array_list)
{
	length_ = array_list.length_;
	size_ = array_list.size_;
	elements_ = new T[length_];
	copy(array_list.elements_, array_list.elements_ + size_, elements_);
}

template<class T>
void CArrayList<T>::CheckIndex(int index) const
{
	if (index < 0 || index >= size_)
	{
		ostringstream s;
		s << "index = " << index << " size = " << size_;
		throw CIllegalIndex(s.str( ));
	}
}

template<class T>
T &CArrayList<T>::get(int index) const
{
	// retrun element whose index is 'index'
	// throw CIllegalIndex exception if no such element.
	CheckIndex(index);
	return elements_[index];
}

template<class T>
int CArrayList<T>::indexof(const T &elem) const
{
	int index = static_cast<int>(find(elements_, elements_ + size_, elem) - elements_);
	if (index == size_) return -1;
	return index;
}

template<class T>
void CArrayList<T>::erase(int index)
{
	// delete the element whose index is 'index'
	// throw CIllegalIndex exception if no such element.
	CheckIndex(index);

	// valid index, shift elements with higher index
	copy(elements_ + index + 1, elements_ + size_, elements_ + index);
	elements_[--size_].~T( ); // invoke destructor
}

template<class T>
void CArrayList<T>::insert(int index, const T &elem)
{
	if (index < 0 || index > size_)
	{
		ostringstream s;
		s << "index = " << index << " size = " << size_;
		throw CIllegalIndex(s.str( ));
	}

	// valid index, make sure we have space
	if (size_ == length_)
	{
		// no space, double capacity
		ChangeLength1D(elements_, length_, 2 * length_);
//		length_ *= 2;
		length_ = length_ << 1;
	}

	// shift elements right one position
	copy_backward(elements_ + index, elements_ + size_, elements_ + size_ + 1);
	elements_[index] = elem;
	size_++;
}

template<class T>
void CArrayList<T>::output(ostream &out) const
{
	copy(elements_, elements_ + size_, ostream_iterator<T>(cout, " "));
}

// overload <<
template<class T>
ostream &operator << (ostream &out, const CArrayList<T> &x)
{
	x.output(out);
	return out;
}

#endif   // ----- #ifndef ARRAY_LIST_INC  -----
