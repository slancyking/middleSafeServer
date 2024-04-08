// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。


std::string rand_str(const int len)  /*参数为字符串的长度*/
{
    /*初始化*/
    std::string str;                 /*声明用来保存随机字符串的str*/
    char c;                     /*声明字符c，用来保存随机生成的字符*/
    int idx;                    /*用来循环的变量*/
    char t;
    /*循环向字符串中添加随机生成的字符*/
    for (idx = 0; idx < len; idx++)
    {
        t = rand() % 62;
        if (t < 10)
            c = '0' + rand() % 10;
        else if (t < 36)
            c = 'a' + rand() % 26;
        else
            c = 'A' + rand() % 26;
        str.push_back(c);
    }
    return str;
}


ServerApi  safeServer;