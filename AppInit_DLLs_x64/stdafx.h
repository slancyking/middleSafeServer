// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>
//
#include <tlhelp32.h>                     //���ڽ��̿��յȺ���
//
#include <shlwapi.h>                      //�����ļ������Ⱥ���
#pragma comment(lib, "shlwapi.lib")
//
#include <stdlib.h>
//
#include <stdio.h>
//
#include <stdarg.h>

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "..\\TSConfig.h"
//
#include "..\\CRegedit\\CRegedit.h"       //ע��� ����
//
#include "..\\COutputlog\\Outputlog.h"    //��� ��־����
//
#include "..\\CRejection\\CRejection.h"   //���������



