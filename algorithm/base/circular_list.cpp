// -------------------------------------------------------------------------------------
// 
//    @filename         :  circular_list.cpp
// 
//    @description      :  test the class CCircularList
// 
//    @version          :  1.0
//    @created          :  2013年06月02日 22时06分06秒
//    @revision         :  none
//    @compiler         :  g++
// 
//    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @company          :  
// 
// -------------------------------------------------------------------------------------

#include <iostream>
#include "circular_list.h"

using namespace std;

int main( )
{
	// test constructor
	CCircularList<int> y, z;

	cout << "initial size of y and z" << endl;
	cout << y.size( ) << ", " << z.size( ) << endl;

	// test insert
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << y << endl;

	// test indexOf
	int index = y.indexof(4);
	if (index < 0) 
		cout << "4 not found" << endl;
	else 
		cout << "The index of 4 is " << index << endl;

	index = y.indexof(7);
	if (index < 0) 
		cout << "7 not found" << endl;
	else 
		cout << "The index of 7 is " << index << endl;
	return 0;
}
