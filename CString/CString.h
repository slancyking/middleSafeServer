// Created by MsNiu on 2018/8/12.
#ifndef ANDROIDPOOK_CESTRING_H
#define ANDROIDPOOK_CESTRING_H
#include <windows.h>
//
#include <string>
//
#include <stdio.h>
//
#include <fcntl.h>
//
#include <memory>
//
#include <list>
//
#include <map>
//
#include <algorithm>    // transform

typedef  unsigned char u8char ;

class CString{

public:
	CString();
	CString(const char    * _fString, ...);
	CString(const wchar_t * _wString);
	~CString();
private:
	
	std::string ascIIString;

public:
	CString & initWithFILE(const char * _pathString);

	CString & initWithUtf8FILE(const char * _pathString);

	CString & initWithFormat(const char * _fString, ...);

	CString & initWithUtf8String(const u8char * _u8String);

	CString & initWithString(const char * _aString);

	void addString(const char    * _aString) {
		if (NULL == _aString) return;
		ascIIString += _aString;
	}

	void addString(const wchar_t * _wString) {
		if (NULL == _wString) return;
		ascIIString += CString::unicode_utf8(_wString);
	}

	void addUtf8String(const u8char * _uString) {
		if (NULL == _uString) return;
		ascIIString += CString::utf8_gb2312(_uString);
	}

	void addFormat(const char * _fString, ...);

	const char * getBuffer() { return ascIIString.c_str(); }

	char at(int sIndex);

	size_t getLenth() { return ascIIString.size(); }

	std::string getUtf8Buffer() {
		return gb2312_utf8(ascIIString.c_str());
	}

	void replace(const char * to_replaced, const char * newchars);

	void trim();

	//��ȡ����ַ���
	std::string left(int Count);

	//��ȡ�м��ַ���
	std::string mid(int Start, int endPos = -1);

	//��ȡ�Ҳ��ַ���
	std::string right(int Count);

	//���ı��м� �ַ� ���������,�����ұߣ�
	std::string getMiddleString(const char * leftStr, const char * rightStr);

	std::string toMiddleString(const char * leftStr, const char * rightStr) {
		ascIIString = getMiddleString(leftStr, rightStr);
		return ascIIString;
	}

	//�ַ����ָ�, ������Ŀ
	int split(const char * splitString, std::list<std::string> & oBuffer);
	//�ַ����ָ�, ������Ŀ
	int split(const char * splitString, std::map<int, std::string> & oBuffer);

	//δ�ҵ�, ���� std::string::npos
	size_t find(const char * findStr, int Start = 0);

	//�Ƿ�Ϊ ��
	bool isEmpty();

	// �����ִ�Сд �Ƚ�
	bool stricmp(const char * cmpString);

	// �����ִ�Сд �Ƚ�
	bool stricmp(std::string  cmpString);

	// ת�� ��д
	void toupper();
	// ת�� Сд
	void tolower();

	// ɾ���ַ���
	void del(size_t iIndex, size_t dCount);
	void del(size_t dCount) {
		this->del(0, dCount);
	}
	void del() {
		ascIIString = "";
	}

	std::string en_base64();
	std::string de_base64();

public:
	bool operator == (const char * _aString) {
		if (NULL == _aString) return false;
		return ascIIString == _aString;
	};
	bool operator != (const char * _aString) {
		if (NULL == _aString) return true;
		return ascIIString != _aString;
	};
	bool operator == (const u8char * _uString) {
		if (NULL == _uString) return false;
		return ascIIString == CString::utf8_gb2312(_uString);
	};
	bool operator != (const u8char * _uString) {
		if (NULL == _uString) return true;
		return ascIIString != CString::utf8_gb2312(_uString);
	};

	CString & operator =  (CString * _u8String) {
		this->ascIIString = _u8String->getBuffer();
		return (*this);
	};
	CString & operator =  (CString _u8String) {
		this->ascIIString = _u8String.getBuffer();
		return (*this);
	};
	CString & operator =  (std::string _aString) {
		this->ascIIString = _aString.c_str();
		return (*this);
	};
	CString & operator =  (const char * _aString) {
		this->ascIIString = _aString;
		return (*this);
	};
	CString & operator =  (const u8char * _uString) {
		this->ascIIString = CString::utf8_gb2312(_uString);
		return (*this);
	};
	CString & operator =  (char * _aString) {
		this->ascIIString = _aString;
		return (*this);
	};
	CString & operator =  (u8char * _uString) {
		this->ascIIString = CString::utf8_gb2312(_uString);
		return (*this);
	};


	CString operator +  (const char * _aString) {
		CString rString = "";
		
		rString.addString(this->ascIIString.c_str());
		rString.addString(_aString);

		return rString;
	};
	CString operator +  (const u8char * _uString) {
		CString rString = "";

		rString.addString(this->ascIIString.c_str());
		rString.addUtf8String(_uString);

		return rString;
	};

	CString & operator += (const char * _aString) {
		this->addString(_aString);
		return (*this);
	};
	CString & operator += (const u8char * _uString) {
		this->addUtf8String(_uString);
		return (*this);
	};

	//���� [] ���� �� n ������
	const char operator [] (int iIndex) {
		return this->at(iIndex);
	}

	//���� = ���� utf8 �ַ���ָ��
	operator const char *() throw(){
		return ascIIString.c_str();
	}

public:

	static std::string	unicode_utf8(const wchar_t * _wString);

	static std::string	unicode_gb2312(const wchar_t * _wString);

	static std::string	utf8_gb2312(const u8char * _u8String);

	static std::string	gb2312_utf8(const char * _aString);

	//����ֵ�ǿ�ʱ, ��Ҫʹ�� free �ӿ��ͷ�
	static wchar_t *	gb2312_unicode(const char * _aString);

	static void		    free(wchar_t * _wString);

	static std::string	format_va(const char * _fString, va_list & args);

	static std::string	format(const char * _fString, ...);

	static CString		CreateWithFILE(const char * _pathString) {
		CString rString;
		return rString.initWithFILE(_pathString);
	}

	static CString		CreateWith_code_gb2312(const char * _aString) {
		CString rString;
		return rString.initWithString(_aString);
	}

	static CString		CreateWith_code_utf8(const u8char * _uString) {
		CString rString;
		return rString.initWithUtf8String(_uString);
	}

	// ����ת��, base64
	static std::string en_base64(const char * _aString);
	static std::string de_base64(const char * _aString);

	//�ַ��� �滻
	static std::string & replace(std::string & SBuffer, const char * to_replaced, const char * newchars);
};
#endif
