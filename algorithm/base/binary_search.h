/// =====================================================================================
/// 
///    @filename         :  binary_search.h
/// 
///    @description      :  折半查找算法定义
/// 
/// -------------------------------------------------------------------------------------
///    @version          :  1.0
///    @created          :  2013年08月03日 01时34分29秒
///    @revision         :  none
///    @compiler         :  g++
/// 
///    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
///    @Company          :  
/// 
/// =====================================================================================

#ifndef  H_BINARY_SEARCH_INC
#define  H_BINARY_SEARCH_INC

template<class T>
int BinarySearch(T a[], int size, const T &key)
{
	// a[0] <= a[1] <= ... <= a[n-1]
	// 如果找到key，返回key所在的位置，否则返回-1
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		int mid = (left + right) >> 1;

		if (key == a[mid]) 
		{
			return mid;
		}
		if (key > a[mid]) 
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return -1;
}

#endif   // ----- #ifndef BINARY_SEARCH_INC  -----
