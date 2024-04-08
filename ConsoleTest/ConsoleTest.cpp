// ConsoleTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <wtypes.h>
#include <tchar.h>
#include <codecvt>

std::string UnicodeToGB18030(const std::wstring& unicodeString)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::string utf8String = conv.to_bytes(unicodeString);

    std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>> convGB18030(new std::codecvt_byname<wchar_t, char, std::mbstate_t>("zh_CN.gb18030"));
    std::wstring gb18030String = convGB18030.from_bytes(utf8String);

    std::string result = conv.to_bytes(gb18030String);
    return result;
}



int main()
{
    std::wstring unicodeString = L"你好，世界！"; // Unicode字符串
    std::string gb18030String = UnicodeToGB18030(unicodeString);
 
    std::cout << "GB18030编码字符串: " << gb18030String << std::endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
