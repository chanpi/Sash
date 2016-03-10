#include "stdafx.h"
#include "SaProcess.h"
#include <Windows.h>

using namespace std;

namespace {
	LPCTSTR g_szSaSleep = _T("SaSleep()");
};

// Sleep(0)の代わりに高パフォーマンスのコンテキストスイッチを行うための関数です。
// 同じ優先順位の他のスレッドの実行の機会を与えます。
// 但し、インテルSSE2に対応していないx86 アーキテクチャーでは no-op となり、何の処理も行わない命令が実行されるか、フォルトが発生します。
// [引数] なし
// http://www.isus.jp/article/parallel-special/benefitting-sleep-loops/
void SaYield( const vector<void*>* /*params*/ ) {
	_mm_pause();
}

// 指定ミリ秒Sleep()を実行します。
// 但し、オーバーヘッドが大きいため、Sleep(0)やSleep(1)などは意図したとおりに動作しない可能性があります。
// [引数]
// DWORD dwMilliseconds; -- スリープする時間（ミリ秒）
// http://www.isus.jp/article/parallel-special/benefitting-sleep-loops/
void SaSleep( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSleep, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSleep, g_szError002 );
	} else {
		DWORD dwMilliseconds = _ttoi((LPCTSTR)(*params)[0]);
		if ( dwMilliseconds <= 1 ) {
			SaYield( params );
		} else {
			Sleep( dwMilliseconds );
		}
	}
}