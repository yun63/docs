/// =====================================================================================
/// 
///    @filename         :  binary_search.cpp
/// 
///    @description      :  折半查找算法的实现
/// 
///    @version          :  1.0
///    @created          :  2013年08月03日 01时32分43秒
///    @revision         :  none
///    @compiler         :  g++
/// 
///    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
///    @company          :  
/// 
/// =====================================================================================

#include <iostream>
#include <iterator>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>

#include "binary_search.h"

using namespace std;

int main( )
{
	int search[7] = {0, 2, 3, 4, 6, 7, 9};
	cout << BinarySearch(search, 7, 4) << endl;

	srand(unsigned(time(NULL)));
	vector<int> vec;
	vec.clear();
	int searchvalue;

	for (int i = 0; i < 10; i++)
	{
		searchvalue = rand() % 100;
		vec.push_back(searchvalue);
	}

	sort(vec.begin(), vec.end());

	cout << "排序过后的随机数组：" << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;

	cout << "指定查找的关键字：" << searchvalue << endl;

	cout << BinarySearch(&vec[0], vec.size(), searchvalue) << endl;

	return 0;
}
