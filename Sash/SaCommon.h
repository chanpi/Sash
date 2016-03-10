#ifndef _SA_COMMON_H_
#define _SA_COMMON_H_

#include <tchar.h>

__declspec(selectany) const TCHAR* g_szTitle = _T("Sash.exe");
__declspec(selectany) const TCHAR* g_szLocale = _T("Japanese");

__declspec(selectany) const TCHAR* g_szFormatS = _T("%s");
__declspec(selectany) const TCHAR* g_szFormatErrorS = _T("%s: %s");
__declspec(selectany) const TCHAR* g_szFormatX = _T("%x");
__declspec(selectany) const TCHAR* g_szFormatMemList = _T("0x%08x | %08x | %s\n");

__declspec(selectany) const TCHAR* g_szHelp = _T("/h");
__declspec(selectany) const TCHAR* g_szUsage = _T("[USAGE] ");

__declspec(selectany) const TCHAR* g_szTRUE = _T("TRUE");
__declspec(selectany) const TCHAR* g_szBar = _T("|");
__declspec(selectany) const TCHAR* g_szHeap = _T("*Heap");

__declspec(selectany) const char* g_szFormatC = "%c";

// ���ϐ���
__declspec(selectany) const TCHAR* g_szSaHwndClassNameParent = _T("SA_HWND_CLASSNAME_PARENT");
__declspec(selectany) const TCHAR* g_szSaHwndWindowNameParent = _T("SA_HWND_WINDOWNAME_PARENT");
__declspec(selectany) const TCHAR* g_szSaHwndClassNameChild = _T("SA_HWND_CLASSNAME_CHILD");
__declspec(selectany) const TCHAR* g_szSaHwndWindowNameChild = _T("SA_HWND_WINDOWNAME_CHILD");

// �G���[���b�Z�[�W
__declspec(selectany) const TCHAR* g_szError000 = _T("[ERROR] ����`�̊֐������w�肳��܂����B\n");
__declspec(selectany) const TCHAR* g_szError001 = _T("[ERROR] �����̎w�肪����Ă��܂�(�����ȃ|�C���^�ł�)�B\n");
__declspec(selectany) const TCHAR* g_szError002 = _T("[ERROR] ����������܂���B\n");
__declspec(selectany) const TCHAR* g_szError003 = _T("[ERROR] �������̊m�ۂɎ��s���܂����B\n");


// ���l
const int g_nName = 256;
const int g_nBufferSize = 2048;

#endif