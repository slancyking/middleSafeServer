#pragma once
//
#include "pch.h"
//
#include "TScript_export.h"
//
#include "..\\XUnrealEngine4\\TScript_UnrealEngine4.h"


typedef  neb::CJsonObject  JSONBuffer;


#define JSONClear(b)					   { b.Clear(); b.Add("error", ""); }

#define JSONWriteValue(b, n, v)            { b.Add(n, v); }
#define JSONWriteValue_Bool(b, n, v)       { b.Add(n, v, v); }
#define JSONWriteValue_UInt64(b, n, v)     { b.Add(n, (double)(ULONGLONG)v); }
#define JSONWriteValue_Double(b, n, v)     { b.Add(n, (double)v); }

#define JSONWriteERRString(b, v)           { b.Clear(); JSONWriteValue(b, "error", v); }

#define JSONArgsAssert(argsJSON, retJSON, key)    {																				\
																if(false == argsJSON.KeyExist(key)){							\
																	retJSON.Clear();											\
																	retJSON.Add("error", "arg invalid : " key);					\
																	return ;													\
																}																\
															  }																	\

#define JSONArgsAssert_Get(argsJSON, retJSON, key, rVar)    {																			\
																		if(false == argsJSON.KeyExist(key)){							\
																			retJSON.Clear();											\
																			retJSON.Add("error", "arg invalid : " key);					\
																			return ;													\
																		}else{															\
																			if(false == argsJSON.Get(key, rVar)){						\
																				retJSON.Clear();										\
																				retJSON.Add("error", "get arg error : " key);			\
																				return ;												\
																			}															\
																		}																\
																	  }																	\

#define JSONArgsTry_Get(argsJSON, key, rVar, defVar)				{																	\
																		if(true == argsJSON.KeyExist(key)){								\
																			if (false == argsJSON.Get(key, rVar)) {						\
																				rVar = defVar;											\
																			}															\
																		}else 	rVar = defVar;											\
																	}																	\



#define CMD_AssertClassSymbol(ivar, _p, _c, _n)				   {																			\
																	do																		\
																	{																		\
																		if (NULL < ivar)													\
																			break;															\
																		UE4$UClass  * _UClass = NULL;										\
																		if (NULL == (_UClass = UE4::findUE4Class(_p, _c))) {				\
																			JSONWriteERRString(retJson, "not find class :" _c);				\
																			return;															\
																		}																	\
																		if (-1 == (ivar = _2UE4IvarOffset(_UClass, _n))) {					\
																			JSONWriteERRString(retJson, "not find " _n);					\
																			return;															\
																		}																	\
																	} while (false);														\
																}																			\



LRESULT CALLBACK FWindowsApplication$AppWndProcCallback(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);

#define __CallSendMessage2Game			FWindowsApplication$AppWndProcCallback










