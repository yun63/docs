// test the class CLinkList
#include<iostream>
#include "linear_list.h"
#include "link_list.h"

using namespace std;

int main()
{
   // test constructor
   CLinearList<double> *x = new CLinkList<double>( );
   CLinkList<int> y, z;

   // test size
   cout << "initial size of x, y, and z = "
        << x->size() << ", "
        << y.size() << ", "
        << z.size() << endl;

   // test empty
   if (x->empty()) 
	   cout << "x is empty" << endl;
   else 
	   cout << "x is not empty" << endl;
   if (y.empty()) 
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
   cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
   cout << "size of y = " << y.size() << endl;

	y.Reverse( );
	cout << "After reverse the list, list y should be 6 5 4 3 2 1" << endl;
	cout << y << endl;

   if (y.empty()) 
	   cout << "y is empty" << endl;
   else 
	   cout << "y is not empty" << endl;
   y.output(cout);
   cout << endl << "Testing overloaded <<" << endl;
   cout << y << endl;

   // test indexOf
   int index = y.indexof(4);
   if (index < 0) cout << "4 not found" << endl;
   else cout << "The index of 4 is " << index << endl;

   index = y.indexof(7);
   if (index < 0) 
	   cout << "7 not found" << endl;
   else 
	   cout << "The index of 7 is " << index << endl;

   // test get
   cout << "element with index 0 is " << y.get(0) << endl;
   cout << "element with index 3 is " << y.get(3) << endl;

   // test erase
   y.erase(1);
   cout << "element with index 1 erased" << endl;
   cout << "the list is:\n" << y << endl;
   y.erase(2);
   cout << "element with index 2 erased" << endl;
   cout << "the list is:\n" << y << endl;
   y.erase(0);
   cout << "element with index 0 erased" << endl;
   cout << "The list is:\n" << y << endl;
   cout << "size of y = " << y.size() << endl;

   if (y.empty()) 
	   cout << "y is empty" << endl;
   else 
	   cout << "y is not empty" << endl;

   try 
   {
	   y.insert(-3, 0);
   }
   catch (CIllegalIndex e)
   {
      cout << "Illegal index exception" << endl;
      cout << "Insert index must be between 0 and list size" << endl;
      e.OutputMessage();
   }

   // test copy constructor
   CLinkList<int> w(y);
   y.erase(0);
   y.erase(0);
   cout << "w should be old y, new y has first 2 elements removed" << endl;
   cout << "w :" << w << endl;
   cout << "y :" << y << endl;
   
   // a few more inserts, just for fun
   y.insert(0,4);
   y.insert(0,5);
   y.insert(0,6);
   y.insert(0,7);
   y.insert(0,4);
   y.insert(0,5);
   y.insert(0,3);
   y.insert(0,6);
   y.insert(0,5);
   y.insert(0,8);
   y.insert(0,9);
   y.insert(0,8);

   y.BinSort(10);

   cout << "y is " << y << endl;

   return 0;
}
