// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"


//字符转换成整形
int hex2int(char c);

/**
 * 字符串替换函数
 * #function name   : replace_str()
 * #param str       : 操作之前的字符串
 * #param before    : 将要被替换的字符串
 * #param after     : 替换目标字符串
 * #return          : void
 */
void replace_str(std::string& str, const std::string& before, const std::string& after);





#define CPPHTTPLIB_OPENSSL_SUPPORT


#endif //PCH_H

 