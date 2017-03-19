// -------------------------------------------------------------------------------------
// 
//    @filename         :  stack.cpp
// 
//    @description      :  顺序栈和链式栈的实现
// 
//    @version          :  1.0
//    @created          :  2013年06月12日 20时34分21秒
//    @revision         :  none
//    @compiler         :  g++
// 
//    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @company          :  
// 
// -------------------------------------------------------------------------------------

#include <iostream>
#include "stack.h"

using namespace std;

int main( )
{
	CSqStack<int> s;                            // 线性栈
	CLinkStack<double> ls;                      // 链式栈

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	ls.push(1.0);
	ls.push(2.0);
	ls.push(3.0);
	ls.push(4.0);
	ls.push(5.0);

	cout << "<<---------- testing linear stack --------->>\n" << endl;

	cout << "stack s should be 1 2 3 4, from bottom to top" << endl;
	if (s.empty( ))
		cout << "stack s is empty" << endl;
	else
		cout << "stack s is not empty" << endl;
	cout << "the size of stack s is : " << s.size( ) << endl;

	while (!s.empty( ))
	{
		cout << "stack s top is " << s.top( ) << endl;
		s.pop( );
		cout << "popped top element" << endl;
	}

	try
	{
		s.pop( );
	}
	catch (CStackEmpty &e)
	{
		cout << "last pop failed" << endl;
		e.OutputMessage( );
	}
	
	cout << endl;

	cout << "<<----------- testing link stack ------------>>\n" << endl;

	if (ls.empty( ))
	{
		cout << "link stack ls is not empty, size = " << ls.size( ) << endl;
	}

	while (!ls.empty( ))
	{
		cout << "top element is " << ls.top( ) << endl;
		ls.pop( );
	}

	try
	{
		ls.pop( );
	}
	catch (CStackEmpty &e)
	{
		cout << "last popped failed" << endl;
		e.OutputMessage( );
	}

	return 0;
}
