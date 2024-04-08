#include "pch.h"
#include "times.h"


UINT64 GetUnixTimeMilliSeconds() {
	SYSTEMTIME lTime;
	GetLocalTime(&lTime);

	struct tm tm;
	memset(&tm, 0, sizeof(tm));

	tm.tm_year = lTime.wYear;
	tm.tm_mon = lTime.wMonth;
	tm.tm_mday = lTime.wDay;

	tm.tm_hour = lTime.wHour;
	tm.tm_min = lTime.wMinute;
	tm.tm_sec = lTime.wSecond;

	tm.tm_year -= 1900;
	tm.tm_mon -= 1;

	return mktime(&tm) * 1000 + lTime.wMilliseconds; 
}


UINT64 GetUnixTime() {
	SYSTEMTIME lTime;
	GetLocalTime(&lTime);

	struct tm tm;
	memset(&tm, 0, sizeof(tm));

	tm.tm_year = lTime.wYear;
	tm.tm_mon = lTime.wMonth;
	tm.tm_mday = lTime.wDay;

	tm.tm_hour = lTime.wHour;
	tm.tm_min = lTime.wMinute;
	tm.tm_sec = lTime.wSecond;

	tm.tm_year -= 1900;
	tm.tm_mon -= 1;

	return mktime(&tm);
}