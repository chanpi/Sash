#ifndef _SA_COMMON_H_
#define _SA_COMMON_H_

#include <tchar.h>

__declspec(selectany) const TCHAR* g_szLocale = _T("Japanese");
__declspec(selectany) const TCHAR* g_szFormatS = _T("%s");
__declspec(selectany) const TCHAR* g_szFormatErrorS = _T("%s: %s");
__declspec(selectany) const TCHAR* g_szHelp = _T("/h");
__declspec(selectany) const TCHAR* g_szUsage = _T("[USAGE] ");
__declspec(selectany) const TCHAR* g_szTRUE = _T("TRUE");
__declspec(selectany) const TCHAR* g_szBar = _T("|");

__declspec(selectany) const char* g_szFormatC = "%c";

// 環境変数名
__declspec(selectany) const TCHAR* g_szSaHwndClassNameParent = _T("SA_HWND_CLASSNAME_PARENT");
__declspec(selectany) const TCHAR* g_szSaHwndWindowNameParent = _T("SA_HWND_WINDOWNAME_PARENT");
__declspec(selectany) const TCHAR* g_szSaHwndClassNameChild = _T("SA_HWND_CLASSNAME_CHILD");
__declspec(selectany) const TCHAR* g_szSaHwndWindowNameChild = _T("SA_HWND_WINDOWNAME_CHILD");

// エラーメッセージ
__declspec(selectany) const TCHAR* g_szError000 = _T("[ERROR] 未定義の関数名が指定されました。\n");
__declspec(selectany) const TCHAR* g_szError001 = _T("[ERROR] 引数の指定が誤っています(無効なポインタです)。\n");
__declspec(selectany) const TCHAR* g_szError002 = _T("[ERROR] 引数が足りません。\n");


// 数値
const int g_nName = 256;
const int g_nBufferSize = 2048;

#endif