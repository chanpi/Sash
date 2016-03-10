#include "stdafx.h"
#include "SaMouse.h"
#include "SaProcess.h"
#include "SaWindow.h"
#include <Windows.h>

using namespace std;

namespace {
	LPCTSTR g_szSaSetCursorPos = _T("SaSetCursorPos()");
	LPCTSTR g_szSaLButtonClick = _T("SaLButtonClick()");
	LPCTSTR g_szSaMButtonClick = _T("SaMButtonClick()");
	LPCTSTR g_szSaRButtonClick = _T("SaRButtonClick()");
};

static void ClickOnAttachedWindowWithSleep( DWORD downType, DWORD upType, DWORD dwSleepMilliseconds );
static void SendMouseInput( DWORD type );

// カーソルを指定位置に移動します。
// [引数]
// int x;
// int y;
void SaSetCursorPos( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError001 );
	} else if ( params->size() < 2 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError002 );
	} else {
		int x = _ttoi((LPCTSTR)(*params)[0]);
		int y = _ttoi((LPCTSTR)(*params)[1]);
		SetCursorPos( x, y );
	}
}

// マウスを左クリックします。内部でSendInput()を使用します。
// [引数] なし
void SaLButtonClick( const vector<void*>* /*params*/ ) {
	SendMouseInput( MOUSEEVENTF_LEFTDOWN );
	SendMouseInput( MOUSEEVENTF_LEFTUP );
}

// マウスを中クリックします。内部でSendInput()を使用します。
// [引数] なし
void SaMButtonClick( const vector<void*>* /*params*/ ) {
	SendMouseInput( MOUSEEVENTF_MIDDLEDOWN );
	SendMouseInput( MOUSEEVENTF_MIDDLEUP );
}

// マウスを右クリックします。内部でSendInput()を使用します。
// [引数] なし
void SaRButtonClick( const vector<void*>* /*params*/ ) {
	SendMouseInput( MOUSEEVENTF_MIDDLEDOWN );
	SendMouseInput( MOUSEEVENTF_MIDDLEUP );
}

// 指定ウィンドウをマウス左ボタンをシングルクリックします。
// 内部でSendInput()を使用します。ウィンドウハンドルは環境変数で設定します。
// ボタンを押してから離すまでのミリ秒間隔を指定します（0ミリ秒以上）。
// [引数] 
// DWORD dwSleepMilliseconds; -- マウスダウンからアップまでの経過時間
void SaLButtonClickOnWindow( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError002 );
	} else {
		DWORD dwSleepMilliseconds = _ttoi((LPCTSTR)(*params)[0]);
		ClickOnAttachedWindowWithSleep( MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP, dwSleepMilliseconds );
	}
}

// 指定ウィンドウをマウス中ボタンをシングルクリックします。
// 内部でSendInput()を使用します。ウィンドウハンドルは環境変数で設定します。
// ボタンを押してから離すまでのミリ秒間隔を指定します（0ミリ秒以上）。
// [引数]
// DWORD dwSleepMilliseconds; -- マウスダウンからアップまでの経過時間
void SaMButtonClickOnWindow( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError002 );
	} else {
		DWORD dwSleepMilliseconds = _ttoi((LPCTSTR)(*params)[0]);
		ClickOnAttachedWindowWithSleep( MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP, dwSleepMilliseconds );
	}
}

// 指定ウィンドウをマウス右ボタンをシングルクリックします。
// 内部でSendInput()を使用します。ウィンドウハンドルは環境変数で設定します。
// ボタンを押してから離すまでのミリ秒間隔を指定します（0ミリ秒以上）。
// [引数]
// DWORD dwSleepMilliseconds; -- マウスダウンからアップまでの経過時間
void SaRButtonClickOnWindow( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError002 );
	} else {
		DWORD dwSleepMilliseconds = _ttoi((LPCTSTR)(*params)[0]);
		ClickOnAttachedWindowWithSleep( MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP, dwSleepMilliseconds );
	}
}

// 入力処理機構を本プログラムにアタッチ後、Sleep処理を加えたクリックを行います。
// Sleep()を使用することで物理的なクリックに近づけます。
// [引数]
// DWORD downType; -- MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_RIGHTDOWN
// DWORD upType; -- MOUSEEVENTF_LEFTUP | MOUSEEVENTF_MIDDLEUP | MOUSEEVENTF_RIGHTUP
// DWORD dwSleepMilliseconds; -- マウスダウンからアップまでの経過時間
void ClickOnAttachedWindowWithSleep( DWORD downType, DWORD upType, DWORD dwSleepMilliseconds ) {
	DWORD dwProcessId = 0;
	DWORD dwThreadId = GetWindowThreadProcessId( GetWindowHandle(), &dwProcessId );
	// 入力を本プログラムのスレッドにアタッチ
	AttachThreadInput( GetCurrentThreadId(), dwThreadId, TRUE );
	SendMouseInput( downType );
	if ( 1 < dwSleepMilliseconds ) {
		Sleep( dwSleepMilliseconds );
	} else {
		SaYield( NULL );
	}
	SendMouseInput( upType );
	if ( 1 < dwSleepMilliseconds ) {
		Sleep( dwSleepMilliseconds );
	} else {
		SaYield( NULL );
	}
	// 入力をデタッチ
	AttachThreadInput( GetCurrentThreadId(), dwThreadId, FALSE );
}

// SendInput関数を利用して、マウスクリックを行います。
void SendMouseInput( DWORD type ) {
	INPUT input[1] = {0};
	MOUSEINPUT mi[1] = {0};

	mi[0].dwFlags = type;
	input[0].type = INPUT_MOUSE;
	input[0].mi = mi[0];
	SendInput(1, input, sizeof(INPUT));
	SaYield( NULL );
}