// -------------------------------------------------------------------------------------
// 
//    @filename         :  sq_queue.cpp
// 
//    @description      :  test sequence queue
// 
//    @version          :  1.0
//    @created          :  2013年06月18日 01时19分46秒
//    @revision         :  none
//    @compiler         :  g++
// 
//    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @company          :  
// 
// -------------------------------------------------------------------------------------

#include <iostream>
#include "queue.h"
#include "exceptions.h"

using namespace std;

int main(void)
{
	CSqueue<int> q(4);
	CLinkQueue<int> lq(4);

	cout << "<<----------- testing linear queue ------------------>>" << endl;
	// add elements
	q.push(1);
	cout << "queue rear is " << q.back( ) << endl;
	q.push(2);
	cout << "queue rear is " << q.back( ) << endl;
	q.push(3);
	cout << "queue rear is " << q.back( ) << endl;
	q.push(4);

	cout << "queue shoule be 1234, front to rear" << endl;

	if (q.empty( ))
		cout << "The queue is empty" << endl;
	else
		cout << "The queue is not empty" << endl;

	cout << "The queue size is " << q.size( ) << endl;

	while (!q.empty( ))
	{
		cout << "The queue front is " << q.front( ) << endl;
		q.pop( );
		cout << "Popped front element" << endl;
	}

	try
	{
		q.pop( );
	}
	catch (CSqueueEmpty e)
	{
		cout << "Last pop failed" << endl;
		e.OutputMessage( );
	}

	// create a wrapround queque and do array doubling
	CSqueue<int> r(4);
	r.push(1);
	r.push(2);
	r.push(3);
	r.pop( );
	r.pop( );
	r.push(4);
	r.push(5);
	r.push(6);
	r.push(7);

	cout << "queue should be 34567, front to rear" << endl;
	if (r.empty( ))
		cout << "The queue is empty" << endl;
	else
		cout << "The queue is not empty" << endl;

	cout << "The queue size is " << r.size( ) << endl;
	
	while (!r.empty( ))
	{
		cout << "Queue front is " << r.front( ) << endl;
		r.pop( );
		cout << "Popped front element" << endl;
	}
	cout << endl;

	cout << "<<----------- testing link queue ------------------>>" << endl;

	lq.push(5);
	cout << "link queue rear is: " << lq.back( ) << endl;
	cout << "link queue front is: " << lq.front( ) << endl;
	lq.push(6);
	cout << "link queue rear is: " << lq.back( ) << endl;
	cout << "link queue front is: " << lq.front( ) << endl;
	lq.push(7);
	cout << "link queue rear is: " << lq.back( ) << endl;
	cout << "link queue front is: " << lq.front( ) << endl;
	lq.push(8);
	cout << "link queue rear is: " << lq.back( ) << endl;
	cout << "link queue front is: " << lq.front( ) << endl;

	cout << "link queue size is: " << lq.size( ) << endl;
	string s = lq.empty( ) ? "empty" : " not empty";
	cout << "link queue is " << s << endl;

	while (!lq.empty( ))
	{
		cout << "link queue front is: " << lq.front( ) << endl;
		lq.pop( );
	}

	cout << "link queue size is: " << lq.size( ) << endl;
	
	try
	{
		lq.pop( );
	}
	catch (CSqueueEmpty &e)
	{
		cout << "popped failed, ";
		e.OutputMessage( );
	}
	lq.push(100);
	lq.clear( );
	lq.pop( );

	return 0;
}
