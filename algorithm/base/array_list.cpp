// -------------------------------------------------------------------------------------
// 
//    @filename         :  array_list.cpp
// 
//    @description      :  test the class CArrayList that uses STL algorithms
// 
//    @version          :  1.0
//    @created          :  2013年06月08日 11时55分13秒
//    @revision         :  none
//    @compiler         :  g++
// 
//    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @company          :  
// 
// -------------------------------------------------------------------------------------

#include <iostream>
#include <numeric>
#include "linear_list.h"
#include "array_list.h"

using namespace std;

int main( )
{
	// test constructor
	CLinearList<double> *x = new CArrayList<double>(20);
	CArrayList<int> y(2), z;
	// test capacity
	cout << "capacity of x, y and z = " 
		 << ((CArrayList<double> *)x)->capacity( ) << ", "
		 << y.capacity( ) << ", "
		 << z.capacity( ) << endl;

	// test size 
	cout << "initial size of x, y, z = "
		 << x->size( ) << ", "
		 << y.size( ) << ", "
		 << z.size( ) << endl;

	// test empty
	if (x->empty( ))
		cout << "x is empty" << endl;
	else
		cout << "x is not empty" << endl;
	if (y.empty( ))
		cout << "y is empty" << endl;
	else
		cout << "y is not empty" << endl;

	// test insert
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "size of y = " << y.size( ) << endl;
	cout << "capacity of y = " << y.capacity( ) << endl;
	if (y.empty( ))
		cout << "y is empty" << endl;
	else
		cout << "y is not empty" << endl;
	y.output(cout);
	cout << endl << "testing overloaded <<" << endl;
	cout << y << endl;

	// test indexof 
	int index = y.indexof(4);
	if (index < 0) 
		cout << "4 not found" << endl;
	else 
		cout << "the index of 4 is " << index << endl;
	index = y.indexof(7);
	if (index < 0)
		cout << "y not found" << endl;
	else
		cout << "the index of 7 is " << index << endl;

	// test get
	cout << "element with index 0 is " << y.get(0) << endl;
	cout << "element with index 3 is " << y.get(3) << endl;

	// test erase
	y.erase(1);
	cout << "index 1 erased" << endl;
	cout << "list is " << y << endl;
	y.erase(2);
	cout << "index 2 erased" << endl;
	cout << "list is " << y << endl;

	cout << "size of y = " << y.size( ) << endl;
	cout << "capacity of y = " << y.capacity( ) << endl;
	if (y.empty( ))
		cout << "y is empty" << endl;
	else
		cout << "y is not empty" << endl;

	try
	{
		y.insert(-3, 0);
	}
	catch (CIllegalIndex e)
	{
		cout << "CIllegal index exception" << endl;
		cout << "insert index must be between 0 and list size" << endl;
		e.OutputMessage( );
	}

	// test copy constructor
	CArrayList<int> w(y);
	y.erase(0);
	y.erase(0);
	cout << "w should be old y, new y has first 2 elements removed" << endl;
	cout << "w is " << w << endl;
	cout << "y is " << y << endl;

	// a few more inserts, just for fun
	y.insert(0, 4);
	y.insert(0, 5);
	y.insert(0, 6);
	y.insert(0, 7);
	cout << "y is " << y << endl;

	// test iterator
	cout << "ouput using forward iterators pre and post ++" << endl;
	for (CArrayList<int>::iterator it = y.begin( );
			it != y.end( ); it++)
	{
		cout << *it << " ";
	}
	for (CArrayList<int>::iterator it = y.begin( );
			it != y.end( ); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "ouput using backward iterators pre and post --" << endl;
	for (CArrayList<int>::iterator it = y.end( );
			it != y.begin( ); cout << *(--it) << " ");
	cout << endl;
	for (CArrayList<int>::iterator it = y.end( );
			it != y.begin( ); )
	{
		it--;
		cout << *it << " ";
		*it += 1;
	}
	cout << endl;
	cout << "incremented by 1 list is " << y << endl;

	// try out some STL algorithms
	reverse(y.begin( ), y.end( ));
	cout << "the reversed list is " << y << endl;
	int sum = accumulate(y.begin( ), y.end( ), 0);
	cout << "the sum of the elements is " << sum << endl;
	return 0;
}
