#pragma once
#include <string>

struct tagServerReport
{
	/// <summary>
	/// ����˵ı�־λ,�����ǽ���id.֮���
	/// </summary>
	std::string flag;
	/// <summary>
	/// ��Կ���� ���ع����� 
	/// </summary>
	int keyIndex;
	/// <summary>
	/// ����˿�
	/// </summary>
	unsigned short randomPort;
	/// <summary>
	/// �����Կ
	/// </summary>
	std::string randomKey;
	/// <summary>
	/// ִ����Ϣ,��ѯ������
	/// </summary>
	std::string info;

	/// <summary>
	/// ִ�д���
	/// </summary>
	int code;
};