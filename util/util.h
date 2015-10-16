
#ifndef  _UTIL_H
#define  _UTIL_H

#include <cstring>
#include <cctype>
#include <climits>
#include <string>

using std::string;

namespace base {

// 剪除左端空格字符
string ltrim(const string &str)
{
    std::string::size_type pos = str.find_first_not_of(' ');
    if (pos == std::string::npos)
    {
        return str;
    }
    return str.substr(pos);
}

// 剪除右端空格字符
string rtrim(const string &str)
{
    std::string::size_type pos = str.find_last_not_of(' ');
    if (pos == std::string::npos)
    {
        return str;
    }
    return str.substr(0, pos + 1);
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

bool getword(const char *str, char *word, int &pos)
{
    if (str[pos] == 0)
    {
        return false;
    }

    const char *p1 = str + pos;
    const char *p2 = p1;
    
    for (int i = 0; i <(int)strlen(p1) && !isalnum(p1[0]); i++)
    {
        ++p1;
    }

    p2 = p1;
    
    while (isalnum(p2[0]))
    {
        ++p2;
    }

    if (p2 == p1) 
    {
        return false;
    }

    int len = static_cast<int>(p2 - p1);
    strncpy(word, p1, len);
    word[len] = '\0';

    for (int i = p2 - str; 
            i < (int)strlen(str) && !isalnum(p2[0]); i++)
    {
        ++p2;
    }

    pos = static_cast<int>(p2 - str);

    return true;
}

}

#endif
