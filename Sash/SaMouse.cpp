#include "stdafx.h"
#include "SaMouse.h"
#include "SaProcess.h"
#include <Windows.h>

using namespace std;

namespace {
	LPCTSTR g_szSaSetCursorPos = _T("SaSetCursorPos()");
	LPCTSTR g_szSaLButtonClick = _T("SaLButtonClick()");
	LPCTSTR g_szSaMButtonClick = _T("SaMButtonClick()");
	LPCTSTR g_szSaRButtonClick = _T("SaRButtonClick()");
};

static void ActMouse( DWORD type );

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

// マウス左ボタンをシングルクリックします。内部でSendInput()を使用します。
// [引数]
// int x;
// int y;
void SaLButtonClick( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaLButtonClick, g_szError001 );
	}
	SaSetCursorPos( params );
	ActMouse( MOUSEEVENTF_LEFTDOWN );
}

// マウス中ボタンをシングルクリックします。内部でSendInput()を使用します。
// [引数]
// int x;
// int y;
void SaMButtonClick( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaMButtonClick, g_szError001 );
	}
	SaSetCursorPos( params );
	ActMouse( MOUSEEVENTF_MIDDLEDOWN );
}

// マウス右ボタンをシングルクリックします。内部でSendInput()を使用します。
// [引数]
// int x;
// int y;
void SaRButtonClick( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaRButtonClick, g_szError001 );
	}
	SaSetCursorPos( params );
	ActMouse( MOUSEEVENTF_RIGHTDOWN );
}

// SendInput関数を利用して、マウスクリックを行います。
void ActMouse( DWORD type ) {
	INPUT input[1] = {0};
	MOUSEINPUT mi[1] = {0};

	mi[0].dwFlags = type;
	input[0].type = INPUT_MOUSE;
	input[0].mi = mi[0];
	SendInput(1, input, sizeof(INPUT));
	SaYield( NULL );
}