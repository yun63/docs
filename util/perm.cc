// =====================================================================================
//
//       Filename:  perms.cc
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年01月16日 15时43分56秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

void permutation(std::string &orig, std::string &perm, unsigned int &count)
{
    if (orig.empty())
    {
        std::cout << perm << std::endl;
        ++count;
        return;
    }

    for (int i = 0; i < orig.size(); ++i)
    {
        std::string orig2 = orig;
        orig2.erase(i, 1);
        std::string perm2 = perm;
        perm2 += orig.at(i);
        permutation(orig2, perm2, count);
    }
}

int main()
{
    std::string s;
    while (std::cin >> s)
    {
        unsigned int count = 0;
        std::string perm("");
        permutation(s, perm, count);
        std::cout << "Compelete! total " << count << " kinds" <<  std::endl;
    }

    return 0;
}
