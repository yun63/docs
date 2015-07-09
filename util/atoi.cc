// =====================================================================================
//
//       Filename:  atoi.cc
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年07月03日 17时51分07秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int myAtoi(string str) {
    int result = 0;
    int sig = 1;
    bool flag = false;

    for (int i =  0; i < str.size(); ++i)
    {
        if (isblank(str[i])) continue;

        if (!flag && str[i] == '-')
        {
            sig = -sig;
            flag = true;
            continue;
        }
        else if (!flag && str[i] == '+')
        {
            flag = true;
            continue;
        }

        if (isdigit(str[i]))
        {
            result = 10 * result + (str[i] - '0');
        }
        else
        {
            break;
        }
    }

    return sig * result;
}

int main()
{
    int result = myAtoi("   +0 123");
    cout << result << endl;
    return 0;
}

