// =====================================================================================
//
//       Filename:  test.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年07月14日 16时43分13秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include <iostream>
#include "util.h"

using namespace std;

int main()
{
    const int kbuffersize = 255;
    char buffer[kbuffersize + 1];
    char word[kbuffersize + 1];
    int pos = 0;

    std::cin.getline(buffer, kbuffersize);

    while (base::getword(buffer, word, pos))
    {
        cout << "Got this word: " << word << endl;
    }

    std::string str = "     hello world     ";
    cout << base::ltrim(str) << endl;
    cout << base::rtrim(str) << endl;
//    cout << base::rtrim((base::ltrim(str)) << std::endl;

    return 0;
}
