#pragma once
#include "Base64.h"



const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";


namespace CBase64 {
	/* Base64 编码 */
	std::string Encode(const char* data) {
		int data_len = 0;
		if (NULL == data || NULL >= (data_len = strlen(data))){
			return std::string("");
		}


		//int data_len = strlen(data); 
		int prepare = 0;
		int ret_len;
		int temp = 0;
		std::string ret = "";

		char *f = NULL;
		int tmp = 0;
		char changed[4];
		int i = 0;
		ret_len = data_len / 3;
		temp = data_len % 3;
		if (temp > 0)
		{
			ret_len += 1;
		}
		ret_len = ret_len * 4 + 1;
		char * newret = (char *)malloc(ret_len);
		if (NULL == newret)
		{
			return std::string("");
		}

		memset(newret, 0, ret_len);
		f = newret;
		while (tmp < data_len)
		{
			temp = 0;
			prepare = 0;
			memset(changed, '\0', 4);
			while (temp < 3)
			{
				//printf("tmp = %d\n", tmp); 
				if (tmp >= data_len)
				{
					break;
				}
				prepare = ((prepare << 8) | (data[tmp] & 0xFF));
				tmp++;
				temp++;
			}
			prepare = (prepare << ((3 - temp) * 8));
			//printf("before for : temp = %d, prepare = %d\n", temp, prepare); 
			for (i = 0; i < 4; i++)
			{
				if (temp < i)
				{
					changed[i] = 0x40;
				}
				else
				{
					changed[i] = (prepare >> ((3 - i) * 6)) & 0x3F;
				}
				*f = base[changed[i]];
				//printf("%.2X", changed[i]); 
				f++;
			}
		}

		*f = '\0';
		ret = newret;
		free(newret);
		return ret;

	}
	/* Base64 解码 */
	std::string  Decode(const char* Data) {
		int DataByte = 0;
		if (NULL == Data || NULL >= (DataByte = strlen(Data))) {
			return std::string("");
		}

		//解码表
		const char DecodeTable[] =
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			62, // '+'
			0, 0, 0,
			63, // '/'
			52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
			0, 0, 0, 0, 0, 0, 0,
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
			13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
			0, 0, 0, 0, 0, 0,
			26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
			39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
		};
		//返回值

		std::string ret = "";
		int nValue = 0;
		int i = 0;
		while (i < DataByte)
		{
			if (*Data != '\r' && *Data != '\n')
			{
				nValue = DecodeTable[*Data++] << 18;
				nValue += DecodeTable[*Data++] << 12;
				ret += (nValue & 0x00FF0000) >> 16;

				if (*Data != '=')
				{
					nValue += DecodeTable[*Data++] << 6;
					ret += (nValue & 0x0000FF00) >> 8;

					if (*Data != '=')
					{
						nValue += DecodeTable[*Data++];
						ret += nValue & 0x000000FF;

					}
				}
				i += 4;
			}
			else// 回车换行,跳过
			{
				Data++;
				i++;
			}
		}
		return ret;
	}
}

