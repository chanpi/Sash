#include "stdafx.h"
#include "SaEnvironmentVariable.h"
#include <Windows.h>

using namespace std;

namespace {
	LPCTSTR g_szSaGetEnvironmentVariable = _T("SaGetEnvironmentVariable()");
};

// 環境変数名の値を出力します。
// [引数]
// LPCTSTR lpName; -- 環境変数名
// [隠し引数]
// LPTSTR szBuffer; -- 環境変数の値を格納するバッファのポインタ
// int nBufferLength; -- バッファサイズ
void SaGetEnvironmentVariable( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaGetEnvironmentVariable, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaGetEnvironmentVariable, g_szError002 );
	} else {
		LPCTSTR lpName = (LPCTSTR)(*params)[0];
		if ( NULL == lpName ) {
			_tprintf_s( g_szFormatErrorS, g_szSaGetEnvironmentVariable, g_szError001 );
		} else {
			TCHAR szBuffer[g_nBufferSize] = {0};
			GetEnvironmentVariable( lpName, szBuffer, _countof(szBuffer));
			_tprintf_s( g_szFormatS, szBuffer );

			// プログラム内部でのみ環境変数の値を受け取れる
			if ( params->size() == 3 ) {
				TCHAR* pBuffer = (TCHAR*)(*params)[1];
				int nBuffer = *((int*)(*params)[2]);
				_tcscpy_s( pBuffer, nBuffer, szBuffer );
			}
		}
	}
}

