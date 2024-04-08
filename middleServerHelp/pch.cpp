// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。


//字符转换成整形
int hex2int(char c)
{
    if ((c >= 'A') && (c <= 'Z'))
    {
        return c - 'A' + 10;
    }
    else if ((c >= 'a') && (c <= 'z'))
    {
        return c - 'a' + 10;
    }
    else if ((c >= '0') && (c <= '9'))
    {
        return c - '0';
    }
    return 0;
}

/**
 * 字符串替换函数
 * #function name   : replace_str()
 * #param str       : 操作之前的字符串
 * #param before    : 将要被替换的字符串
 * #param after     : 替换目标字符串
 * #return          : void
 */
void replace_str(std::string& str, const std::string& before, const std::string& after)
{
    for (std::string::size_type pos(0); pos != std::string::npos; pos += after.length())
    {
        pos = str.find(before, pos);
        if (pos != std::string::npos)
            str.replace(pos, before.length(), after);
        else
            break;
    }
}