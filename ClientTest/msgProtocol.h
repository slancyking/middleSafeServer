#pragma once  

#define hTableSize 10
#define hTableFlag 10

// ��Ϸ ��Կ��� .�˿����   -->> �ϱ�������  -->>  ���ص���������֤ , ͨ�� �õ� ��Կ.�˿�

using typeOfTable = UINT;

struct tagMsgHeader
{
	UINT hSize = 0;
	UINT fackDataSize = 0; //�����ݳ���
	typeOfTable  hTable[hTableSize] = { NULL };
	INT64 uTime = 0;
	//��ǰ������
	UINT8 getDayIdx() {
		struct tm mytm;
		localtime_s(&mytm ,&uTime);
		return mytm.tm_mday % hTableSize;
	}

	//�������ͷ����
	void genaralRandTable(size_t bufSize) {
		UINT8 idx = getDayIdx(); 
		typeOfTable sumHash = 0;
		for (UINT8 i = 0; i < hTableSize; i++)
		{
			hTable[i] = (rand() << 15) + rand();
			if (idx != i) { 
				sumHash = hTable[i] / hTableFlag << 2;
			}
		} 
		hTable[idx] = bufSize + sumHash * 2;
		fackDataSize += sumHash * 3;
	}

	//��ȡ����������
	typeOfTable getBufSize() {
		UINT8 idx = getDayIdx();
		typeOfTable sumHash = 0;
		for (UINT8 i = 0; i < hTableSize; i++)
		{
			if (idx != i) { 
				sumHash = hTable[i] / hTableFlag << 2;
			}
		} 
		return hTable[idx] - sumHash * 2;
	}
	
	//��������ݳ���
	typeOfTable getFackDataSize() {
		UINT8 idx = getDayIdx();
		typeOfTable sumHash = 0;
		for (UINT8 i = 0; i < hTableSize; i++)
		{
			if (idx != i) {
				sumHash = hTable[i] / hTableFlag << 2;
			}
		}
		return fackDataSize - sumHash * 3;
	}


	tagMsgHeader(size_t bufSize) {
		srand(GetTickCount64());
		uTime = std::time(0);
		hSize = sizeof(tagMsgHeader);
		fackDataSize = rand() % 64 * sizeof(typeOfTable);
		genaralRandTable(bufSize);
	}
};



class sendMsgProtocol
{
public:

	sendMsgProtocol(std::string msg,std::string key);
	 
	void* getData(UINT& size);
	void genaralFackData(UINT size);
	~sendMsgProtocol();
private:
	tagMsgHeader* header = NULL;
	void* dataBuffer = NULL;
	size_t dataSize = 0; 
	UINT fackDataSize = 0;
};


class recvMsgProtocol {
public:
	recvMsgProtocol(void* data, size_t dataSize);
	~recvMsgProtocol();

	std::string getMsg(std::string key);
	tagMsgHeader* header = NULL;
private:

	void* dataBuffer = NULL;

	size_t dataSize = 0;
};