#include "pch.h"
#include "msgProtocol.h" 
 

sendMsgProtocol::sendMsgProtocol(std::string msg, std::string key)
{
	if (msg.size() == 0) { return; } 
	void* dBuf = xxtea_encrypt(msg.data(), msg.size(), key.c_str(), &dataSize); 
	  
	header = new tagMsgHeader(dataSize);
	UINT fackSize = header->getFackDataSize();
	UINT allSize = sizeof(tagMsgHeader) + dataSize + fackSize;
	dataBuffer = malloc(allSize);
	if (dataBuffer == NULL)
		return;
	ZeroMemory(dataBuffer, allSize);

	memcpy(dataBuffer, header, sizeof(tagMsgHeader));
	genaralFackData(fackSize);
	memcpy((void*)((size_t)dataBuffer + sizeof(tagMsgHeader) + fackSize), dBuf, dataSize);
	dataSize = allSize;
	free(dBuf);
}
  
void* sendMsgProtocol::getData(UINT& size)
{
	size = dataSize;
	return dataBuffer;
}

void sendMsgProtocol::genaralFackData(UINT size)
{
	UINT round = size / (sizeof(typeOfTable));
	typeOfTable* gPos = (typeOfTable*)((size_t)dataBuffer + sizeof(tagMsgHeader));
	for (UINT i = 0; i < round; i++)
	{
		gPos[i] = (rand() << 15) + rand();
	} 
}

sendMsgProtocol::~sendMsgProtocol()
{
	if (header != NULL)
		delete header;

	if (dataBuffer != NULL) 
		free(dataBuffer);
	 

}

recvMsgProtocol::recvMsgProtocol(void* data, size_t dataSize)
{
	UINT headSize = sizeof(tagMsgHeader); 
	header = (tagMsgHeader*)malloc(headSize);
	if (header == NULL)
		return;
	ZeroMemory(header, headSize);
	memcpy(header, data, headSize);
	UINT fackSize = header->getFackDataSize();
	UINT realSize = header->getBufSize();

	if (static_cast<unsigned long long>(fackSize) + realSize + headSize != dataSize)
		return;

	this->dataSize = realSize;

	dataBuffer = malloc(realSize);
	if (dataBuffer == NULL)
		return;

	memcpy(dataBuffer, (void*)((size_t)data + fackSize + headSize), realSize);
}

recvMsgProtocol::~recvMsgProtocol()
{
	if (header != NULL)
		free(header);

	if (dataBuffer != NULL)
		free(dataBuffer);
}

std::string recvMsgProtocol::getMsg(std::string key)
{
	size_t strSize = 0;
	char* cStr = (char*)xxtea_decrypt(dataBuffer, dataSize, key.c_str(), &strSize);
	if (cStr == NULL)
		return "";
	std::string result(cStr);
	free(cStr);
	return result;
}
