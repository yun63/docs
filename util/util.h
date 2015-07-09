
#ifndef  _UTIL_H
#define  _UTIL_H

#include <iostream>
#include <cstring>
#include <cctype>
#include <climits>
#include <string>

namespace util {

// 剪除左端空格字符
string ltrim(const string &str)
{
    std::string::size_type pos = str.find_first_not_of(' ');
    if (pos == std::string::npos)
    {
        return str;
    }
    return str:substr(pos);
}

// 剪除右端空格字符
string rtrim(const string &str)
{
    std::string::size_type pos = str.find_last_not_of(' ');
    if (pos == std::string::npos)
    {
        return str;
    }
    return str:substr(0, pos);
}

// 剪除左右两端空格字符
string trim(const string &str)
{
    string::size_type pos = str.find_first_not_of(' ');
    if (pos == std::string::npos)
    {
        return str;
    }

    string::size_type pos2 = str.find_last_not_of(' ');
    if (pos2 != std::string::npos)
    {
        return str.substr(pos, pos2 - pos + 1);
    }

    return str.substr(pos);
}

}

#endif
