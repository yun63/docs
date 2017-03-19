// -------------------------------------------------------------------------------------
// 
//    @filename         :  ll_iterator.cpp
// 
//    @description      :  
//
// -------------------------------------------------------------------------------------
//    @version          :  1.0
//    @created          :  2013年06月01日 16时21分07秒
//    @revision         :  none
//    @compiler         :  g++
// 
//    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @Company          :  
// 
// -------------------------------------------------------------------------------------


#include <iostream>
#include <numeric>
#include "linear_list.h"
#include "link_list.h"
#include "exceptions.h"

using namespace std;

int main( )
{
	CLinkList<int> y;
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "inserted 6 integers, list y should be 1->2->3->4->5->6" << endl;
	cout << "size of y : " << y.size( ) << endl;
	// test iterator
	cout << "output using forward iterators pre and post ++" << endl;
	for (CLinkList<int>::iterator it = y.begin( );
			it != y.end( ); ++it)
	{
		cout << *it << "	";
	}
	cout << endl;
	for (CLinkList<int>::iterator it = y.begin( );
			it != y.end( ); ++it)
	{
		cout << *it << "	";
		*it += 1;
	}
	cout << endl;

	cout << "incremented by 1 list is : " << endl;
	cout << y << endl;
	
	int sum = accumulate(y.begin( ), y.end( ), 0);
	cout << "the sum of the elements is : " << sum << endl;
	return 0;
}
